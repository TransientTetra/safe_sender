#include <iostream>
#include "model/communication/session.hpp"

Session::Session(tcp::socket &&socket)
: socket(std::move(socket))
{

}

void Session::start()
{
	asio::async_read_until(socket, buffer, '\n', [self = shared_from_this()] (asio::error_code error, std::size_t bytes_transferred)
	{
		std::cout << std::istream(&self->buffer).rdbuf();
	});
}
