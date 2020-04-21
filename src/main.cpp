#include <iostream>
#include <string>
#include "../include/controller/application.hpp"
#include "../include/model/text_message.hpp"
#include "../include/model/encryption/encryption_aes.hpp"
#include "../include/model/raw_bytes.hpp"
#include "../include/model/file.hpp"
#include <crypto++/randpool.h>
#include <crypto++/aes.h>
#include <crypto++/osrng.h>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;
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
template<class T> T receive_signal(tcp::socket &socket, unsigned long size)
{
	boost::asio::streambuf buf(size);
	boost::asio::read( socket, buf);
	return T(*boost::asio::buffer_cast<const char*>(buf.data()));
}
template<class T> void send_signal(tcp::socket &socket, T msg, unsigned long size)
{
	boost::asio::write(socket, boost::asio::buffer(&msg, size));
}
RawBytes receive(tcp::socket &socket, unsigned long size)
{
	boost::asio::streambuf buf(size);
	boost::asio::read( socket, buf);
	return RawBytes(boost::asio::buffer_cast<const char*>(buf.data()));
}
void send(tcp::socket &socket, Sendable msg)
{
	boost::asio::write(socket, boost::asio::buffer(&msg.getData(), msg.getDataSize()));
}

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		std::cerr << "safe_sender <ip> <is_server ? 1 : 0>\n";
		return 1;
	}
	std::string ip_to_send_to = argv[1];
	bool is_server = *argv[2] != '0';

	boost::asio::io_service io_service;
	//listen for new connection
	tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1234 ));
	//socket creation
	tcp::socket socket(io_service);
	if (is_server)
	{
		acceptor.accept(socket);
		MessageType r = receive_signal<MessageType>(socket, sizeof(MessageType));
		if (r == TXT_MSG)
		{
			send_signal<ResponseType>(socket, ACCEPT, sizeof(ResponseType));
		}
		else
		{
			send_signal<ResponseType>(socket, REJECT, sizeof(ResponseType));
			return 15;
		}
		unsigned long size = receive_signal<unsigned long>(socket, sizeof(unsigned long));
		std::cout << size << std::flush;
		std::cout << receive(socket, size).toString();
	}
	else
	{
		bool server_accepted;
		TextMessage str("no siemano");
		//connect can throw Connection refused if there's no server to connect to or sth
		socket.connect(tcp::endpoint(boost::asio::ip::address::from_string(ip_to_send_to), 1234));
		boost::system::error_code e;
		MessageType msg = TXT_MSG;
		send_signal<MessageType>(socket, msg, sizeof(MessageType));

		ResponseType rsp = receive_signal<ResponseType>(socket, sizeof(ResponseType));
		server_accepted = rsp == ACCEPT;
		if (server_accepted)
		{
			send_signal<unsigned long>(socket, str.getDataSize(), sizeof(unsigned long));
			send(socket, str);
		}
	}
	return 0;
}