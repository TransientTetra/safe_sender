#include <iostream>
#include <model/communication/session.hpp>
#include "../../../include/model/communication/receiver.hpp"
#include "../../../include/model/encryption/encryption_aes.hpp"
#include "controller/application.hpp"

Receiver::Receiver(asio::io_service &ioService, unsigned int port, Application* application)
: Communicator(ioService), acceptor(ioService, tcp::endpoint(tcp::v4(), port))
{
	this->application = application;
	this->port = port;
	connected = false;
}

void Receiver::listen()
{
	acceptor.async_accept(socket, std::bind(&Receiver::handleAccept, this));
}

void Receiver::handleAccept()
{
	std::make_shared<Session>(std::move(socket), application)->start();
	listen();
}
