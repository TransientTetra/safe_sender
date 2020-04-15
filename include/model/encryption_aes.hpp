#ifndef SAFE_SENDER_ENCRYPTION_AES_HPP
#define SAFE_SENDER_ENCRYPTION_AES_HPP
#include "encryption.hpp"

class EncryptionAES : public Encryption
{
private:
	CipherMode cipherMode;
protected:
public:
	EncryptionAES(CipherMode cipherMode);
	RawBytes encrypt(const RawBytes &data);
};


#endif //SAFE_SENDER_ENCRYPTION_AES_HPP
