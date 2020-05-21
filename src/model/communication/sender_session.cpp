#include "model/communication/sender_session.hpp"

SenderSession::SenderSession(tcp::socket &&socket, Application *application)
: Session(std::move(socket), application)
{}

void SenderSession::start()
{

}
