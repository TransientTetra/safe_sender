#ifndef SAFE_SENDER_APPLICATION_HPP
#define SAFE_SENDER_APPLICATION_HPP


#include <string>
#include <model/communication/receiver.hpp>
#include <model/communication/sender.hpp>
#include <view/window.hpp>
#include <model/encryption/encryption.hpp>


class Application
{
private:
	//todo make progressbars work
	std::string title;
	std::thread receiverThread;
	Receiver* receiver;
	Sender* sender;
	Window window;
protected:
public:
	Application(std::string title);

	void run();
};


#endif //SAFE_SENDER_APPLICATION_HPP
