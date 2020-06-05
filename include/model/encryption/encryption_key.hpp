#ifndef SAFE_SENDER_ENCRYPTION_KEY_HPP
#define SAFE_SENDER_ENCRYPTION_KEY_HPP


#include "encryptable.hpp"
#include "../communication/sendable.hpp"

class EncryptionKey : public Encryptable, public Sendable
{
private:
protected:
public:
	EncryptionKey();
	EncryptionKey(const std::string& str);
	EncryptionKey(RawBytes bytes);
	~EncryptionKey();

	std::string toString();
};


#endif //SAFE_SENDER_ENCRYPTION_KEY_HPP
