#ifndef SAFE_SENDER_RECEIVER_HPP
#define SAFE_SENDER_RECEIVER_HPP

#include <thread>
#include "communicator.hpp"
#include "../raw_bytes.hpp"
class Application;
class Receiver : public Communicator
{
private:
	std::string senderIP;
	tcp::acceptor acceptor;

	Application* application;

protected:
public:
	Receiver(asio::io_service &ioService, unsigned int port, Application* application);

	void listen();
	void handleAccept();
};


#endif //SAFE_SENDER_RECEIVER_HPP
