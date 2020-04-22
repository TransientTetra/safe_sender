#include "../../../include/model/communication/sender.hpp"

#include <utility>

Sender::Sender(boost::asio::io_service &ioService)
: socket(ioService), connected(false)
{

}

Sender::Sender(boost::asio::io_service &ioService, std::string ip, unsigned int port)
: socket(ioService), receiverIP(std::move(ip)), receiverPort(port), connected(false)
{

}

const std::string &Sender::getReceiverIP() const
{
	return receiverIP;
}

const unsigned int &Sender::getReceiverPort() const
{
	return receiverPort;
}

void Sender::setReceiverIPAndPort(std::string ip, unsigned int port)
{
	receiverIP = ip;
	receiverPort = port;
	connected = false;
}

bool Sender::connect()
{
	try
	{
		//connect can throw Connection refused if there's no server to connect to or sth
		socket.connect(boost::asio::ip::tcp::tcp::endpoint(
			boost::asio::ip::address::from_string(receiverIP), receiverPort));
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