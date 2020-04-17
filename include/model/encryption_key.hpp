#ifndef SAFE_SENDER_ENCRYPTION_KEY_HPP
#define SAFE_SENDER_ENCRYPTION_KEY_HPP


#include "encryptable.hpp"
#include "sendable.hpp"

class EncryptionKey : public Encryptable, public Sendable
{
private:
protected:
public:
	EncryptionKey();
	EncryptionKey(const std::string& str);
	EncryptionKey(RawBytes bytes);
};


#endif //SAFE_SENDER_ENCRYPTION_KEY_HPP
