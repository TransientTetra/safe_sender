#include <iostream>
#include <model/encryption/encryption_aes.hpp>
#include "model/communication/receiver_session.hpp"

ReceiverSession::ReceiverSession(tcp::socket &&socket, Application* application)
: Session(std::move(socket), application)
{
}

void ReceiverSession::start()
{
	try
	{
		handleIncoming(receiveKey());
	}
	catch(std::exception e)
	{
		//this handles when for example sender disconnects
	}
}


RawBytes ReceiverSession::receive(unsigned long size)
{
	asio::streambuf buf(size);
	asio::read(socket, buf);
	return RawBytes(asio::buffer_cast<const unsigned char*>(buf.data()), size);
}

void ReceiverSession::handleIncoming(CryptoPP::RSA::PublicKey receivedKey)
{
	sendKey(application->getPublicKey());
	std::unique_ptr<Encryption> encryption;
	RawBytes temp = receiveEncryptedPacket();
	application->getEncryption().decrypt(temp);

	Packet packet;
	packet.deserialize(reinterpret_cast<const char *>(temp.BytePtr()));
	bool isEncrypted = packet.isEncrypted;

	//constructing the message to ask user
	std::string displayQuestion = "Incoming ";
	if (packet.messageType == FILE_MSG)
	{
		displayQuestion += "file " + std::string(packet.filename) + packet.extension;
	}
	else
		displayQuestion += "text message";
	displayQuestion += ". Do you accept?";

	Packet responsePacket;
	if (!application->askYesNo(displayQuestion))
	{
		responsePacket.responseType = REJECT;
		sendPacket(responsePacket);
		return;
	}
	responsePacket.responseType = ACCEPT;
	sendPacket(responsePacket);
	try
	{
		FileMetadata metadata;
		if (isEncrypted)
		{
			encryption.reset(new EncryptionAES(packet.cipherMode));
			EncryptionKey aesKey = receive(packet.keySize);
			encryption->setEncryptionKey(aesKey);
			encryption->setIV(packet.iv);
		}
		if (packet.messageType == FILE_MSG)
		{
			metadata.filename = std::string(packet.filename);
			metadata.extension = std::string(packet.extension);
			//todo messagesize been observed as 0, check
			metadata.dataSize = packet.messageSize;
		}
		
		std::unique_ptr<DataContainer> msg;
		switch (packet.messageType)
		{
			case TXT_MSG:
				msg.reset(new TextMessage(receive(packet.messageSize)));
				if (isEncrypted) dynamic_cast<TextMessage*>(msg.get())->decrypt(*encryption);
				application->displayError("Received message: " +
					dynamic_cast<TextMessage*>(msg.get())->toString());
				break;
			case FILE_MSG:
				msg.reset(new File(receive(packet.messageSize)));
				if (isEncrypted) dynamic_cast<File*>(msg.get())->decrypt(*encryption);
				dynamic_cast<File*>(msg.get())->setMetadata(metadata);
				dynamic_cast<File*>(msg.get())->save(application->askPath());
				break;
			default:
				break;
		}
	}
	catch (std::exception &e)
	{
		application->displayError(std::string("Error while receiving data:\n") + e.what());
	}
}
