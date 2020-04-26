#ifndef SAFE_SENDER_COMMUNICATOR_HPP
#define SAFE_SENDER_COMMUNICATOR_HPP

#include "boost/asio.hpp"

enum MessageType
{
	TXT_MSG,
	FILE_MSG
};
enum ResponseType
{
	ACCEPT,
	REJECT
};

class Communicator
{
private:
protected:
	boost::asio::ip::tcp::tcp::socket socket;
	unsigned int port;
	bool connected;
public:
	Communicator(boost::asio::io_service &ioService);
	template<class T> void sendSignal(T msg)
	{
		boost::asio::write(socket, boost::asio::buffer(&msg, sizeof(T)));
	}
	template<class T> T receiveSignal()
	{
		boost::asio::streambuf buf(sizeof(T));
		boost::asio::read( socket, buf);
		return T(*boost::asio::buffer_cast<const char*>(buf.data()));
	}
};


#endif //SAFE_SENDER_COMMUNICATOR_HPP