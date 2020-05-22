#include "model/communication/sender_session.hpp"

SenderSession::SenderSession(tcp::socket &&socket, Application *application)
: Session(std::move(socket), application)
{}


float SenderSession::getProgress() const
{
	return progress;
}

void SenderSession::sendBinary(Sendable &data)
{
	asio::write(socket, asio::buffer(data.getData().BytePtr(), data.getDataSize()));
}

void SenderSession::sendFile(File &file, EncryptionKey &key, InitializationVector &iv, CipherMode mode)
{
	application->setState(SENDING);
	try
	{
		Packet packet;
		packet.messageType = FILE_MSG;
		packet.messageSize = file.getDataSize();
		packet.ivSize = iv.getDataSize();
		packet.keySize = key.getDataSize();
		packet.isEncrypted = file.isEncrypted();
		packet.cipherMode = mode;
//setting metadata info
		strcpy(packet.filename, file.getMetadata().filename.c_str());
		strcpy(packet.extension, file.getMetadata().extension.c_str());
		sendPacket(packet);
		Packet response = receivePacket();
		if (response.responseType != ACCEPT)
		{
			application->displayError("Error: Receiver rejected the file");
			return;
		}
		if (file.isEncrypted())
		{
			sendBinary(key);
			sendBinary(iv);
		}

		sendBinary(file);
	}
	catch (std::exception &e)
	{
		application->displayError(std::string("Error: Sending file failed:\n") + e.what());
	}
//this is a hack
//	disconnect();
//	connect();
	application->setState(CONNECTED);
}

void SenderSession::sendTxtMsg(TextMessage &msg, EncryptionKey &key, InitializationVector &iv, CipherMode m)
{
	application->setState(SENDING);
	try
	{
		Packet packet;
		packet.isEncrypted = msg.isEncrypted();
		packet.messageType = TXT_MSG;
		packet.messageSize = msg.getDataSize();
		if (msg.isEncrypted())
		{
			packet.ivSize = iv.getDataSize();
			packet.keySize = key.getDataSize();
			packet.cipherMode = m;
		}
		sendPacket(packet);
		Packet response = receivePacket();
		if (response.responseType != ACCEPT)
		{
			application->displayError("Error: Receiver rejected the message");
			return;
		}
		if (msg.isEncrypted())
		{
			sendBinary(key);
			sendBinary(iv);
		}
		sendBinary(msg);
	}
	catch (std::exception &e)
	{
		application->displayError(std::string("Error: Sending text message failed:\n") + e.what());
	}
	//this is a hack
//	disconnect();
//	connect();
	application->setState(CONNECTED);
}
