#include "../../../include/model/communication/communicator.hpp"

Communicator::Communicator(asio::io_service &ioService)
: socket(ioService)
{

}
Communicator::Communicator(tcp::socket&& socket)
: socket(std::move(socket))
{

}

void Communicator::sendPacket(Packet packet)
{
	char *buffer = serializePacket(packet);
	asio::write(socket, asio::buffer(buffer, sizeof(Packet)));
	delete[] buffer;
}

Packet Communicator::receivePacket()
{
	asio::streambuf buf(sizeof(Packet));
	asio::read(socket, buf);
	const char *buffer = asio::buffer_cast<const char*>(buf.data());
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