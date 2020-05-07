#ifndef SAFE_SENDER_RECEIVER_HPP
#define SAFE_SENDER_RECEIVER_HPP

#include <thread>
#include <boost/enable_shared_from_this.hpp>
#include "communicator.hpp"
#include "../raw_bytes.hpp"
class Application;
class Receiver : public Communicator
{
private:
	std::string senderIP;
	boost::asio::ip::tcp::tcp::acceptor acceptor;

	Application* application;

	RawBytes receive(unsigned long size);
protected:
public:
	Receiver(boost::asio::io_service &ioService, unsigned int port);

	void open();

	std::thread getListenerThread();
	void listen();
	void attachApplication(Application *application);
};


#endif //SAFE_SENDER_RECEIVER_HPP
