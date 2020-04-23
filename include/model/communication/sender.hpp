#ifndef SAFE_SENDER_SENDER_HPP
#define SAFE_SENDER_SENDER_HPP

#include "../raw_bytes.hpp"
#include "sendable.hpp"
#include "communicator.hpp"

class Sender : public Communicator
{
private:
	std::string receiverIP;
protected:
public:
	//constructor used by client when sending data
	Sender(boost::asio::io_service &ioService, std::string ip, unsigned int port);

	void setReceiverIPAndPort(std::string ip, unsigned int port);

	const std::string &getReceiverIP() const;
	const unsigned int &getReceiverPort() const;

	bool connect();
	void send(Sendable &data);
};


#endif //SAFE_SENDER_SENDER_HPP
