#include "model/communication/session.hpp"

Session::Session(tcp::socket &&socket, Application *application)
: Communicator(std::move(socket))
{
	this->application = application;
}
