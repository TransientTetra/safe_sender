#include "../../../include/model/communication/sender.hpp"
#include "../../../include/model/encryption/encryption_key.hpp"
#include "../../../include/model/initialization_vector.hpp"

#include <utility>
#include <iostream>

Sender::Sender(std::string ip, unsigned int port)
: Communicator(), receiverIP(std::move(ip))
{
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
//		socket.connect(boost::asio::ip::tcp::tcp::endpoint(
//			boost::asio::ip::address::from_string(receiverIP), port));
		connected = true;
	}
	catch (std::exception &e)
	{
		return false;
	}
	return true;
}

void Sender::send(Sendable &data)
{
//	boost::asio::write(socket, boost::asio::buffer(data.getData().BytePtr(), data.getDataSize()));
}

void Sender::sendFile(File &file, bool isEncrypted, EncryptionKey &key, InitializationVector &iv, CipherMode mode)
{
	try
	{
		Packet packet;
		packet.messageType = FILE_MSG;
		packet.messageSize = file.getDataSize();
		packet.ivSize = iv.getDataSize();
		packet.keySize = key.getDataSize();
		packet.isEncrypted = isEncrypted;
		packet.cipherMode = mode;
		if (receivePacket().responseType != ACCEPT)
		{
			//todo handle server rejection
		}
		if (isEncrypted)
		{
			send(key);
			send(iv);
		}
		//todo send metadata here
		send(file);
	}
	catch (std::exception &e)
	{
		std::cerr << "Sending file failed\n" << std::flush;
	}
}

void Sender::sendTxtMsg(TextMessage &msg, bool isEncrypted, EncryptionKey &key, InitializationVector &iv, CipherMode m)
{
	try
	{
		Packet packet;
		packet.messageType = TXT_MSG;
		packet.messageSize = msg.getDataSize();
		packet.ivSize = iv.getDataSize();
		packet.keySize = key.getDataSize();
		packet.isEncrypted = isEncrypted;
		packet.cipherMode = m;
		sendPacket(packet);
		if (receivePacket().responseType != ACCEPT)
		{
			//todo handle server rejection
		}
		if (isEncrypted)
		{
			send(key);
			send(iv);
		}
		send(msg);
	}
	catch (std::exception &e)
	{
		std::cerr << "Sending text message failed\n" << std::flush;
	}
}

float Sender::getProgress()
{
	//todo implement
	return 0;
}
