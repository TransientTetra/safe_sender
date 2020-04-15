#ifndef SAFE_SENDER_ENCRYPTION_KEY_HPP
#define SAFE_SENDER_ENCRYPTION_KEY_HPP


#include "raw_bytes.hpp"
#include <crypto++/secblock.h>

class EncryptionKey
{
private:
	RawBytes key;
	int length;
protected:
public:
	EncryptionKey();
	EncryptionKey(CryptoPP::SecByteBlock byteBlock);

	void setKey(std::string str);
	int getLength() const;
};


#endif //SAFE_SENDER_ENCRYPTION_KEY_HPP
