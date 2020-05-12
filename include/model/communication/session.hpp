#ifndef SAFE_SENDER_SESSION_HPP
#define SAFE_SENDER_SESSION_HPP

#include <asio.hpp>
#include <memory>
#include <controller/application.hpp>

using namespace asio::ip;

class Session : public std::enable_shared_from_this<Session>, Communicator
{
private:
	asio::streambuf buffer;
	Application *application;

	void handleIncoming(Packet packet);
	RawBytes receive(unsigned long size);
protected:
public:
	Session(tcp::socket&& socket, Application* application);

	void start();
};


#endif //SAFE_SENDER_SESSION_HPP
