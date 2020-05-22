#include "model/communication/sender.hpp"
#include "controller/application.hpp"

#include <utility>
#include <iostream>
#include <model/communication/sender_session.hpp>

Sender::Sender(asio::io_service &ioService, std::string ip, unsigned int port, Application* application)
: Communicator(ioService), receiverIP(std::move(ip))
{
	this->application = application;
	this->port = port;
	connected = false;
	progress = 0;
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
	if (connected) disconnect();
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

//todo when receiver rejects message the next one is error: eof
void Sender::handleSend(DataContainer* msg, EncryptionKey &key, InitializationVector &iv,
			CipherMode mode, MessageType type)
{
	application->setState(SENDING);
	Packet packet;
	packet.messageType = type;
	packet.messageSize = msg->getDataSize();
	packet.ivSize = iv.getDataSize();
	packet.keySize = key.getDataSize();
	packet.isEncrypted = dynamic_cast<Encryptable*>(msg)->isEncrypted();
	packet.cipherMode = mode;
	if (type == FILE_MSG)
	{
		//setting metadata info
		strcpy(packet.filename, dynamic_cast<File*>(msg)->getMetadata().filename.c_str());
		strcpy(packet.extension, dynamic_cast<File*>(msg)->getMetadata().extension.c_str());
	}
	sendPacket(packet);
	std::make_shared<SenderSession>(std::move(socket), application, msg, key, iv, mode, type)->start();
}

float Sender::getProgress()
{
	return progress;
}

void Sender::disconnect()
{
	socket.close();
	connected = false;
	application->setState(DISCONNECTED);
}

Sender::~Sender()
{
	if (connected) disconnect();
}
