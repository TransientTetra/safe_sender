#include "../../../include/model/communication/communicator.hpp"

Communicator::Communicator()
{

}

void Communicator::sendPacket(Packet packet)
{
	//todo
	char *buffer = serializePacket(packet);
//	boost::asio::write(socket, boost::asio::buffer(buffer, sizeof(Packet)));
	delete[] buffer;
}

Packet Communicator::receivePacket()
{
	//todo
//	boost::asio::streambuf buf(sizeof(Packet));
//	boost::asio::read(socket, buf);
//	const char *buffer = boost::asio::buffer_cast<const char*>(buf.data());
//	return deserializePacket(buffer);
return Packet();
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