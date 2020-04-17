#ifndef SAFE_SENDER_ENCRYPTION_HPP
#define SAFE_SENDER_ENCRYPTION_HPP
#include <string>
#include "raw_bytes.hpp"

enum CipherMode
{
	ECB,
	CBC,
	CFB,
	OFB
};
//a virtual class that all encryption algorithms must inherit from
class Encryption
{
private:
protected:
	RawBytes encryptionKey;
	RawBytes initializationVector;
public:
	virtual void encrypt(RawBytes &data) = 0;
	virtual void decrypt(RawBytes &data) = 0;

	virtual void setEncryptionKey(std::string str);
	virtual void setEncryptionKey(RawBytes &bytes);
	virtual void setIV(std::string str);
	virtual void setIV(RawBytes &bytes);
};


#endif //SAFE_SENDER_ENCRYPTION_HPP
