#ifndef SAFE_SENDER_SENDER_HPP
#define SAFE_SENDER_SENDER_HPP


#include <boost/asio.hpp>
#include "../raw_bytes.hpp"
#include "sendable.hpp"

enum MessageType
{
	TXT_MSG,
	FILE_MSG,
	KEY,
	IV
};
enum ResponseType
{
	ACCEPT,
	REJECT
};
class Sender
{
private:
	std::string receiverIP;
	unsigned int receiverPort;
	boost::asio::ip::tcp::tcp::socket socket;
	bool connected;

protected:
public:
	//constructor used by server when sending signals
	Sender(boost::asio::io_service &ioService);
	//constructor used by client when sending data
	Sender(boost::asio::io_service &ioService, std::string ip, unsigned int port);

	void setReceiverIPAndPort(std::string ip, unsigned int port);

	const std::string &getReceiverIP() const;
	const unsigned int &getReceiverPort() const;

	bool connect();
	void send(Sendable &data);

	template<class T> ResponseType sendSignal(T msg, int size)
	{
		boost::asio::write(socket, boost::asio::buffer(&msg, size));
		//todo handle server responses
		return ACCEPT;
	}
};


#endif //SAFE_SENDER_SENDER_HPP
