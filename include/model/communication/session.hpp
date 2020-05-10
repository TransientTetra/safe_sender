#ifndef SAFE_SENDER_SESSION_HPP
#define SAFE_SENDER_SESSION_HPP

#include <asio.hpp>
#include <memory>

using namespace asio::ip;

class Session : public std::enable_shared_from_this<Session>
{
private:
	tcp::socket socket;
	asio::streambuf buffer;
protected:
public:
	Session(tcp::socket&& socket);

	void start();
};


#endif //SAFE_SENDER_SESSION_HPP
