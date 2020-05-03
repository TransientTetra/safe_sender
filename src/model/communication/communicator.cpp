#include "../../../include/model/communication/communicator.hpp"

Communicator::Communicator(boost::asio::io_service &ioService)
: socket(ioService)
{

}

void Communicator::sendPacket(Packet packet)
{
	char *buffer = new char[sizeof(Packet)];
	memcpy(buffer, &packet, sizeof(Packet));
	boost::asio::write(socket, boost::asio::buffer(&buffer, sizeof(Packet)));
	delete[] buffer;
}

Packet Communicator::receivePacket()
{
	boost::asio::streambuf buf(sizeof(Packet));
	boost::asio::read( socket, buf);
	char *buffer = boost::asio::buffer_cast<char*>(buf.data());
	Packet ret;
	memcpy(&ret, buffer, sizeof(Packet));
	return ret;
}
