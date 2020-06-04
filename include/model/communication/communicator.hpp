#ifndef SAFE_SENDER_COMMUNICATOR_HPP
#define SAFE_SENDER_COMMUNICATOR_HPP

#include <asio.hpp>
#include <constants.hpp>
#include <cryptopp/rsa.h>
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
	char sessionKey[DEFAULT_SESSION_KEY_SIZE];
	char iv[DEFAULT_IV_SIZE];

	std::shared_ptr<char> serialize();
	void deserialize(const char* arr);
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
	virtual void sendEncryptedPacket(RawBytes bytes);
	virtual RawBytes receiveEncryptedPacket();
	virtual void sendKey(CryptoPP::RSA::PublicKey& key);
	virtual CryptoPP::RSA::PublicKey receiveKey();
};


#endif //SAFE_SENDER_COMMUNICATOR_HPP