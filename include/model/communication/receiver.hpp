#ifndef SAFE_SENDER_RECEIVER_HPP
#define SAFE_SENDER_RECEIVER_HPP

#include "communicator.hpp"
#include "../raw_bytes.hpp"

class Receiver : public Communicator
{
private:
	std::string senderIP;
	boost::asio::ip::tcp::tcp::acceptor acceptor;
protected:
public:
	Receiver(boost::asio::io_service &ioService, unsigned int port);

	void open();
	RawBytes receive(unsigned long size);
};


#endif //SAFE_SENDER_RECEIVER_HPP
