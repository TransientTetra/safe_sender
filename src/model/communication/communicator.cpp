#include "../../../include/model/communication/communicator.hpp"

Communicator::Communicator(boost::asio::io_service &ioService)
: socket(ioService)
{

}

void Communicator::sendPacket(Packet packet)
{
	char *buffer = serializePacket(packet);
	boost::asio::write(socket, boost::asio::buffer(buffer, sizeof(Packet)));
	delete[] buffer;
}

Packet Communicator::receivePacket()
{
	boost::asio::streambuf buf(sizeof(Packet));
	boost::asio::read( socket, buf);
	const char *buffer = boost::asio::buffer_cast<const char*>(buf.data());
	return deserializePacket(buffer);
}

char *Communicator::serializePacket(Packet packet)
{
	char *buffer = new char[sizeof(Packet)];
	memcpy(buffer, &packet, sizeof(Packet));
	return buffer;
}

Packet Communicator::deserializePacket(const char *binary)
{
	Packet ret;
	memcpy(&ret, binary, sizeof(Packet));
	return ret;
}
