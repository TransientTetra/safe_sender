#ifndef SAFE_SENDER_ENCRYPTION_HPP
#define SAFE_SENDER_ENCRYPTION_HPP
#include <string>
#include "../raw_bytes.hpp"
#include "encryption_key.hpp"
#include "../initialization_vector.hpp"

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
	CipherMode cipherMode;
	EncryptionKey encryptionKey;
	InitializationVector initializationVector;
public:
	virtual void encrypt(RawBytes &data) = 0;
	virtual void decrypt(RawBytes &data) = 0;

	virtual const EncryptionKey getEncryptionKey() const;
	virtual void setEncryptionKey(EncryptionKey &key);

	virtual const InitializationVector getInitializationVector() const;
	virtual void setIV(InitializationVector &iv);
};


#endif //SAFE_SENDER_ENCRYPTION_HPP
