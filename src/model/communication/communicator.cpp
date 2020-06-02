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
	std::shared_ptr<char> buffer = packet.serialize();
	asio::write(socket, asio::buffer(buffer.get(), sizeof(Packet)));
}

Packet Communicator::receivePacket()
{
	asio::streambuf buf(sizeof(Packet));
	asio::read(socket, buf);
	const char *buffer = asio::buffer_cast<const char*>(buf.data());
	Packet ret;
	ret.deserialize(buffer);
	return ret;
}

std::shared_ptr<char> Packet::serialize()
{
	std::shared_ptr<char> ret;
	ret.reset(new char[sizeof(Packet)]);
	memcpy(ret.get(), this, sizeof(Packet));
	return ret;
}

void Packet::deserialize(const char *arr)
{
	memcpy(this, arr, sizeof(Packet));
}
