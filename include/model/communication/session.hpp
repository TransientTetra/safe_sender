#ifndef SAFE_SENDER_SESSION_HPP
#define SAFE_SENDER_SESSION_HPP


#include <asio.hpp>
#include <memory>
#include <controller/application.hpp>

using namespace asio::ip;

class Session : public std::enable_shared_from_this<Session>, public Communicator
{
private:
protected:
	asio::streambuf buffer;
	Application *application;
public:
	Session(tcp::socket&& socket, Application* application);

	virtual void start() = 0;
};


#endif //SAFE_SENDER_SESSION_HPP
