#ifndef SAFE_SENDER_ENCRYPTION_AES_HPP
#define SAFE_SENDER_ENCRYPTION_AES_HPP
#include "encryption.hpp"

class EncryptionAES : public Encryption
{
private:
	CipherMode cipherMode;
	RawBytes encryptionKey;
	RawBytes initializationVector;

	void encryptECB(RawBytes &data);
	void encryptCBC(RawBytes &data);
	void encryptCFB(RawBytes &data);
	void encryptOFB(RawBytes &data);
protected:
public:
	EncryptionAES(CipherMode cipherMode);
	void encrypt(RawBytes &data);

	void setEncryptionKey(std::string str);
};


#endif //SAFE_SENDER_ENCRYPTION_AES_HPP
