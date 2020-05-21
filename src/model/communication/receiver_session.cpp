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
		handleIncoming(receivePacket());
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
	return RawBytes(asio::buffer_cast<const char*>(buf.data()));
}

void ReceiverSession::handleIncoming(Packet packet)
{
	//todo sometimes the incoming data is corrupted
	Packet responsePacket;
	std::unique_ptr<Encryption> encryption;
	bool isEncrypted = packet.isEncrypted;

	//constructing the message to ask user
	std::string displayQuestion = "Incoming ";
	displayQuestion += (packet.messageType == TXT_MSG ? "text message" : "file");
	displayQuestion += ". Do you accept?";

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
			InitializationVector iv = receive(packet.ivSize);
			encryption->setEncryptionKey(aesKey);
			encryption->setIV(iv);
		}
		if (packet.messageType == FILE_MSG)
		{
//			asio::streambuf buf(packet.metadataSize);
//			asio::read(socket, buf);
//			const char *buffer = asio::buffer_cast<const char*>(buf.data());
//			memcpy(&metadata, buffer, packet.metadataSize);
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
