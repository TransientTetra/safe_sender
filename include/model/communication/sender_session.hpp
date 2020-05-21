#ifndef SAFE_SENDER_SENDER_SESSION_HPP
#define SAFE_SENDER_SENDER_SESSION_HPP


#include "session.hpp"

class SenderSession : public Session
{
private:
//	DataContainer& data;
//	EncryptionKey& key;
//	InitializationVector& iv;
//	CipherMode cipherMode;

	void sendData();
protected:
public:
	SenderSession(tcp::socket &&socket, Application *application);

	void start() override;
};


#endif //SAFE_SENDER_SENDER_SESSION_HPP
