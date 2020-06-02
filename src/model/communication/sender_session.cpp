#include "model/communication/sender_session.hpp"

SenderSession::SenderSession(tcp::socket &&socket, Application *application, DataContainer* msg,
	Encryption& encryption, MessageType messageType)
: Session(std::move(socket), application), packetBuffer(sizeof(Packet))
{
	this->msg = msg;
	this->messageType = messageType;
	if (dynamic_cast<Encryptable*>(msg)->isEncrypted())
	{
		this->key = const_cast<EncryptionKey *>(&(encryption.getEncryptionKey()));
		cipherMode = encryption.getCipherMode();
	}
}


float SenderSession::getProgress() const
{
	return progress;
}

void SenderSession::sendBinary(Sendable &data)
{
	asio::write(socket, asio::buffer(data.getData().BytePtr(), data.getDataSize()));
}

void SenderSession::start()
{
	//todo make this multithreaded
	//asio::async_read(socket, packetBuffer, std::bind(&SenderSession::handleResponse, this));
	asio::read(socket, packetBuffer);
	handleResponse();
}

void SenderSession::handleResponse()
{
	const char *buffer = asio::buffer_cast<const char*>(packetBuffer.data());
	Packet response;
	response.deserialize(buffer);
	if (response.responseType == ACCEPT)
		sendData();
	else
		application->displayError("Error: Receiver rejected the data");
}

void SenderSession::sendData()
{
	try
	{
		if (dynamic_cast<Encryptable*>(msg)->isEncrypted())
		{
			sendBinary(*key);
		}

		sendBinary(*dynamic_cast<Sendable*>(msg));
	}
	catch (std::exception &e)
	{
		application->displayError(std::string("Error: Sending data failed:\n") + e.what());
	}
	application->setState(CONNECTED);
}
