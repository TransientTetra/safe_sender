#include <iostream>
#include <model/encryption/encryption_aes.hpp>
#include <cryptopp/osrng.h>
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
	Packet packet;
	if (application->isLoginCorrect())
	{
		application->getEncryption().decrypt(temp);

		packet.deserialize(reinterpret_cast<const char *>(temp.BytePtr()));
	}

	//constructing the message to ask user
	std::string displayQuestion = "Incoming ";
	if (application->isLoginCorrect())
	{
		if (packet.messageType == FILE_MSG)
		{
			displayQuestion += "file " + std::string(packet.filename) + packet.extension;
		}
		else
			displayQuestion += "text message";
	}
	else
		displayQuestion += "???";
	displayQuestion += ". Do you accept?";

	Packet responsePacket;
	EncryptionRSA e;
	e.setPublicKey(receivedKey);
	bool userAccepted = application->askYesNo(displayQuestion);
	if (not userAccepted or not application->isLoginCorrect())
	{
		responsePacket.responseType = REJECT;
		RawBytes temp2(reinterpret_cast<const unsigned char *>(responsePacket.serialize().get()), sizeof(Packet));
		e.encrypt(temp2);
		sendEncryptedPacket(temp2);
		if (not application->isLoginCorrect() and userAccepted)
		{
			CryptoPP::AutoSeededRandomPool rng;
			CryptoPP::Integer randomDataSize(rng, MIN_RANDOM_DATA_SIZE, MAX_RANDOM_DATA_SIZE);
			RawBytes data(0x00, randomDataSize.ConvertToLong());
			rng.GenerateBlock(data, data.size());
			TextMessage msg(data);
			application->displayError("Received message: " + msg.toString());
		}
		return;
	}
	responsePacket.responseType = ACCEPT;
	RawBytes temp2(reinterpret_cast<const unsigned char *>(responsePacket.serialize().get()), sizeof(Packet));
	e.encrypt(temp2);
	sendEncryptedPacket(temp2);

	try
	{
		FileMetadata metadata;
		if (packet.isEncrypted)
		{
			encryption.reset(new EncryptionAES(packet.cipherMode));
			//todo
			char key[packet.keySize + 1];
			memcpy(key, packet.sessionKey, sizeof(key) - 1);
			key[packet.keySize] = '\0';
			EncryptionKey aesKey(std::string(key, packet.keySize));
			encryption->setEncryptionKey(aesKey);
			//todo
			char iv[DEFAULT_IV_SIZE + 1];
			memcpy(iv, packet.iv, sizeof(iv) - 1);
			iv[DEFAULT_IV_SIZE] = '\0';
			encryption->setIV(iv);
		}
		if (packet.messageType == FILE_MSG)
		{
			metadata.filename = std::string(packet.filename);
			metadata.extension = std::string(packet.extension);
			metadata.dataSize = packet.messageSize;
		}
		
		std::unique_ptr<DataContainer> msg;
		switch (packet.messageType)
		{
			case TXT_MSG:
				msg.reset(new TextMessage(receive(packet.messageSize)));
				if (packet.isEncrypted) dynamic_cast<TextMessage*>(msg.get())->decrypt(*encryption);
				application->displayError("Received message: " +
					dynamic_cast<TextMessage*>(msg.get())->toString());
				break;
			case FILE_MSG:
				msg.reset(new File(receive(packet.messageSize)));
				if (packet.isEncrypted) dynamic_cast<File*>(msg.get())->decrypt(*encryption);
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
