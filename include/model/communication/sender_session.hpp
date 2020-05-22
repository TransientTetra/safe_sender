#ifndef SAFE_SENDER_SENDER_SESSION_HPP
#define SAFE_SENDER_SENDER_SESSION_HPP


#include "session.hpp"

class SenderSession : public Session
{
private:
	float progress;
	void sendData();
	void sendBinary(Sendable &data);
protected:
public:
	SenderSession(tcp::socket &&socket, Application *application);

	float getProgress() const;
	void sendFile(File &file, EncryptionKey &key, InitializationVector &iv, CipherMode mode);
	void sendTxtMsg(TextMessage &msg, EncryptionKey &key, InitializationVector &iv, CipherMode m);
};


#endif //SAFE_SENDER_SENDER_SESSION_HPP
