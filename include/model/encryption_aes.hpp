#ifndef SAFE_SENDER_ENCRYPTION_AES_HPP
#define SAFE_SENDER_ENCRYPTION_AES_HPP
#include "encryption.hpp"
#include "encryption_key.hpp"

class EncryptionAES : public Encryption
{
private:
	CipherMode cipherMode;
	EncryptionKey key;
protected:
public:
	EncryptionAES(CipherMode cipherMode);
	RawBytes encrypt(const RawBytes &data);

	void setEncryptionKey(std::string str);
};


#endif //SAFE_SENDER_ENCRYPTION_AES_HPP
