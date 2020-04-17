#ifndef SAFE_SENDER_ENCRYPTION_AES_HPP
#define SAFE_SENDER_ENCRYPTION_AES_HPP
#include "encryption.hpp"

class EncryptionAES : public Encryption
{
private:
	CipherMode cipherMode;

	void encryptECB(RawBytes &data);
	void encryptCBC(RawBytes &data);
	void encryptCFB(RawBytes &data);
	void encryptOFB(RawBytes &data);

	void decryptECB(RawBytes &data);
	void decryptCBC(RawBytes &data);
	void decryptCFB(RawBytes &data);
	void decryptOFB(RawBytes &data);
protected:
public:
	EncryptionAES(CipherMode cipherMode);
	void encrypt(RawBytes &data);
	void decrypt(RawBytes &data);
};


#endif //SAFE_SENDER_ENCRYPTION_AES_HPP
