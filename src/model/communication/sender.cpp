#include "../../../include/model/communication/sender.hpp"

#include <utility>

Sender::Sender(boost::asio::io_service &ioService, std::string ip, unsigned int port)
: Communicator(ioService), receiverIP(std::move(ip))
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