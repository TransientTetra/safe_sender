#ifndef SAFE_SENDER_COMMUNICATOR_HPP
#define SAFE_SENDER_COMMUNICATOR_HPP

#include "boost/asio.hpp"
#include "model/encryption/encryption.hpp"

enum MessageType
{
	TXT_MSG,
	FILE_MSG
};
enum ResponseType
{
	ACCEPT,
	REJECT
};

struct Packet
{
	MessageType messageType;
	ResponseType responseType;
	CipherMode cipherMode;
	unsigned long messageSize;
	unsigned long ivSize;
	unsigned long keySize;
	bool isEncrypted;
};

class Communicator
{
private:
protected:
	boost::asio::ip::tcp::tcp::socket socket;
	unsigned int port;
	bool connected;


public:
	std::mutex mutex;

	Communicator(boost::asio::io_service &ioService);
	virtual void sendPacket(Packet frame);
	virtual Packet receivePacket();

	virtual char *serializePacket(Packet packet);
	virtual Packet deserializePacket(const char* binary);
};


#endif //SAFE_SENDER_COMMUNICATOR_HPP