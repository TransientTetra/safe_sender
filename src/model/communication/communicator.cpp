#include <model/file.hpp>
#include <model/encryption/encryption_rsa.hpp>
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

void Communicator::sendKey(CryptoPP::RSA::PublicKey& key)
{
	std::string tempPath = "/tmp/temp.dat";
	EncryptionRSA encryption;
	encryption.setPublicKey(key);
	encryption.savePublicKey(tempPath);
	File tempFile(tempPath);

	asio::write(socket, asio::buffer(tempFile.getData().BytePtr(), tempFile.getData().size()));
}

CryptoPP::RSA::PublicKey Communicator::receiveKey()
{
	std::string tempPath = "/tmp/tempReceived.dat";
	CryptoPP::RSA::PublicKey ret;
	asio::streambuf buf(RSA_KEY_TRANSFER_SIZE);
	asio::read(socket, buf);
	const char *buffer = asio::buffer_cast<const char*>(buf.data());
	File tempFile(RawBytes(reinterpret_cast<const unsigned char *>(buffer), RSA_KEY_TRANSFER_SIZE));
	tempFile.save(tempPath);
	EncryptionRSA encryption;
	encryption.loadPublicKey(tempPath);
	return encryption.getPublicKey();
}

void Communicator::sendEncryptedPacket(RawBytes temp)
{
	asio::write(socket, asio::buffer(temp.BytePtr(), temp.size()));
}

RawBytes Communicator::receiveEncryptedPacket()
{
	int size = PACKET_ENCRYPTED_SIZE;
	asio::streambuf buf(size);
	asio::read(socket, buf);
	return RawBytes(asio::buffer_cast<const unsigned char*>(buf.data()), size);
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
