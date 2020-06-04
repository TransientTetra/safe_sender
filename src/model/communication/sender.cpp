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

//todo when receiver rejects message the sender is disconnected (feature?)
//todo files not getting sent (img)
void Sender::handleSend(DataContainer* msg, Encryption& encryption, MessageType messageType)
{
	application->setState(SENDING);
	Packet packet;
	packet.messageType = messageType;
	packet.messageSize = msg->getDataSize();
	packet.isEncrypted = dynamic_cast<Encryptable*>(msg)->isEncrypted();
	if (packet.isEncrypted)
	{
		packet.keySize = encryption.getEncryptionKey().getDataSize();
		packet.cipherMode = encryption.getCipherMode();
		strcpy(packet.iv, encryption.getIV().c_str());
	}
	if (messageType == FILE_MSG)
	{
		//setting metadata info
		strcpy(packet.filename, dynamic_cast<File*>(msg)->getMetadata().filename.c_str());
		strcpy(packet.extension, dynamic_cast<File*>(msg)->getMetadata().extension.c_str());
	}
	sendKey(application->getPublicKey());
	CryptoPP::RSA::PublicKey receiverKey = receiveKey();
	EncryptionRSA e;
	e.setPublicKey(receiverKey);
	RawBytes temp(reinterpret_cast<const unsigned char *>(packet.serialize().get()), sizeof(Packet));
	e.encrypt(temp);
	sendPacket(packet);
	std::make_shared<SenderSession>(std::move(socket), application, msg, encryption, messageType)->start();
	//this is a hack
	disconnect();
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
