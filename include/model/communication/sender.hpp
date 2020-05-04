#ifndef SAFE_SENDER_SENDER_HPP
#define SAFE_SENDER_SENDER_HPP

#include "../raw_bytes.hpp"
#include "sendable.hpp"
#include "communicator.hpp"
#include "../file.hpp"
#include "../text_message.hpp"
#include "../encryption/encryption_key.hpp"
#include "../initialization_vector.hpp"

class Sender : public Communicator
{
private:
	std::string receiverIP;
	void send(Sendable &data);
protected:
public:
	//constructor used by client when sending data
	Sender(boost::asio::io_service &ioService, std::string ip, unsigned int port);

	void setReceiverIPAndPort(std::string ip, unsigned int port);

	const std::string &getReceiverIP() const;
	const unsigned int &getReceiverPort() const;

	bool connect();
	void sendFile(File &file, EncryptionKey &key, InitializationVector &iv, bool isEncrypted);
	void sendTxtMsg(TextMessage &msg, EncryptionKey &key, InitializationVector &iv, bool isEncrypted);
};


#endif //SAFE_SENDER_SENDER_HPP
