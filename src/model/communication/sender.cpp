#include "model/communication/sender.hpp"
#include "controller/application.hpp"

#include <utility>
#include <iostream>
#include <model/communication/receiver_session.hpp>

Sender::Sender(asio::io_service &ioService, std::string ip, unsigned int port, Application* application)
: Communicator(ioService), receiverIP(std::move(ip))
{
	this->application = application;
	this->port = port;
	connected = false;
}

const std::string &Sender::getReceiverIP() const
{
	return receiverIP;
}

const unsigned int &Sender::getReceiverPort() const
{
	return port;
}

void Sender::setReceiverIPAndPort(std::string ip, unsigned int port)
{
	receiverIP = ip;
	this->port = port;
	connected = false;
}

bool Sender::connect()
{
	try
	{
		//connect can throw Connection refused if there's no server to connect to or sth
		socket.connect(tcp::endpoint(address::from_string(receiverIP), port));
		connected = true;
	}
	catch (std::exception &e)
	{
		return false;
	}
	return true;
}

void Sender::sendBinary(Sendable &data)
{
	asio::write(socket, asio::buffer(data.getData().BytePtr(), data.getDataSize()));
}

//todo merge below two functions
//todo when receiver rejects message the next one is error: eof
//todo transition to sender session
void Sender::handleSendFile(File &file, EncryptionKey &key, InitializationVector &iv, CipherMode mode)
{
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
	disconnect();
	connect();
}

void Sender::handleSendTxtMsg(TextMessage &msg, EncryptionKey &key, InitializationVector &iv, CipherMode m)
{
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
	disconnect();
	connect();
}

float Sender::getProgress()
{
	//todo implement
	return 0;
}

void Sender::disconnect()
{
	socket.cancel();
	socket.close();
	connected = false;
}

Sender::~Sender()
{
	if (connected) disconnect();
}
