#ifndef SAFE_SENDER_COMMUNICATOR_HPP
#define SAFE_SENDER_COMMUNICATOR_HPP

#include <asio.hpp>
#include <constants.hpp>
#include "model/encryption/encryption.hpp"

using namespace asio::ip;

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
	unsigned long keySize;
	bool isEncrypted;
	char filename[PACKET_CHAR_BUFFER_SIZE];
	char extension[PACKET_CHAR_BUFFER_SIZE];
	char publicKey[DEFAULT_KEY_SIZE];
	char iv[DEFAULT_IV_SIZE];
};

class Communicator
{
private:
protected:
	tcp::socket socket;
	unsigned int port;
	bool connected;


public:
	std::mutex mutex;

	Communicator(asio::io_service &ioService);
	Communicator(tcp::socket&& socket);
	virtual void sendPacket(Packet frame);
	virtual Packet receivePacket();

	static char *serializePacket(Packet packet);
	static Packet deserializePacket(const char* binary);
};


#endif //SAFE_SENDER_COMMUNICATOR_HPP