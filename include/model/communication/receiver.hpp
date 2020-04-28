#ifndef SAFE_SENDER_RECEIVER_HPP
#define SAFE_SENDER_RECEIVER_HPP

#include <thread>
#include "communicator.hpp"
#include "../raw_bytes.hpp"

class Receiver : public Communicator
{
private:
	std::string senderIP;
	boost::asio::ip::tcp::tcp::acceptor acceptor;

	RawBytes receive(unsigned long size);
protected:
public:
	Receiver(boost::asio::io_service &ioService, unsigned int port);

	void open();

	void listenAndReceive();
	std::thread threadListenAndReceive();
};


#endif //SAFE_SENDER_RECEIVER_HPP
