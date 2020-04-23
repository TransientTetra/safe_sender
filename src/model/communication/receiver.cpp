#include "../../../include/model/communication/receiver.hpp"

Receiver::Receiver(boost::asio::io_service &ioService, unsigned int port)
: Communicator(ioService),
acceptor(ioService, boost::asio::ip::tcp::tcp::endpoint(boost::asio::ip::tcp::tcp::v4(), port))
{
	this->port = port;
	connected = false;
}

void Receiver::open()
{
	acceptor.accept(socket);
}

RawBytes Receiver::receive(unsigned long size)
{
	boost::asio::streambuf buf(size);
	boost::asio::read(socket, buf);
	return RawBytes(boost::asio::buffer_cast<const char*>(buf.data()));
}