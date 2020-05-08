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

	Application* application;

	RawBytes receive(unsigned long size);
protected:
public:
	Receiver(unsigned int port);

	void open();

	std::thread getListenerThread();
	void listen();
	void attachApplication(Application *application);
};


#endif //SAFE_SENDER_RECEIVER_HPP
