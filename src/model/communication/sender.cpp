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
		socket.connect(boost::asio::ip::tcp::tcp::endpoint(
			boost::asio::ip::address::from_string(receiverIP), port));
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
	boost::asio::write(socket, boost::asio::buffer(data.getData().BytePtr(), data.getDataSize()));
}

void Sender::sendFile(File &file, EncryptionKey &key, InitializationVector &iv, bool isEncrypted)
{
	try
	{
		sendSignal(FILE_MSG);
		if (receiveSignal<ResponseType>() != ACCEPT)
		{
			//todo handle server rejection
		}
		sendSignal(isEncrypted);
		if (isEncrypted)
		{
			sendSignal(key.getDataSize());
			send(key);
			sendSignal(iv.getDataSize());
			send(iv);
		}
		//todo send metadata here
		sendSignal(file.getDataSize());
		send(file);
	}
	catch (std::exception &e)
	{
		std::cerr << "Sending file failed\n" << std::flush;
	}
}

void Sender::sendTxtMsg(TextMessage &msg, EncryptionKey &key, InitializationVector &iv, bool isEncrypted)
{
	try
	{
		sendSignal(TXT_MSG);
		if (receiveSignal<ResponseType>() != ACCEPT)
		{
			//todo handle server rejection
		}
		sendSignal(isEncrypted);
		if (isEncrypted)
		{
			sendSignal(key.getDataSize());
			send(key);
			sendSignal(iv.getDataSize());
			send(iv);
		}
		sendSignal(msg.getDataSize());
		send(msg);
	}
	catch (std::exception &e)
	{
		std::cerr << "Sending text message failed\n" << std::flush;
	}
}
