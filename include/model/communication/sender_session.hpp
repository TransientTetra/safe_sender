#ifndef SAFE_SENDER_SENDER_SESSION_HPP
#define SAFE_SENDER_SENDER_SESSION_HPP


#include "session.hpp"

class SenderSession : public Session
{
private:
	DataContainer* msg;
	EncryptionKey* key;
	CipherMode cipherMode;
	MessageType messageType;
	float progress;
	asio::streambuf packetBuffer;

	void sendData();
	void sendBinary(Sendable &data);
	void handleResponse();
protected:
public:
	SenderSession(tcp::socket &&socket, Application *application, DataContainer* msg,
		Encryption& encryption, MessageType messageType);

	void start() override;

	float getProgress() const;
};


#endif //SAFE_SENDER_SENDER_SESSION_HPP
