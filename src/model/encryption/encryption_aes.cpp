#include "model/encryption/encryption_aes.hpp"
#include <ostream>
#include "cryptopp/aes.h"
#include "cryptopp/modes.h"
#include <constants.hpp>

void EncryptionAES::encrypt(RawBytes &data)
{
	switch (cipherMode)
	{
		case ECB:
			encryptECB(data);
			break;
		case CBC:
			encryptCBC(data);
			break;
		case CFB:
			encryptCFB(data);
			break;
		case OFB:
			encryptOFB(data);
			break;
	}
}

EncryptionAES::EncryptionAES(CipherMode cipherMode)
{
	this->cipherMode = cipherMode;
}

void EncryptionAES::encryptECB(RawBytes &data)
{

}

void EncryptionAES::encryptCBC(RawBytes &data)
{

}

void EncryptionAES::encryptCFB(RawBytes &data)
{
	CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption encryption(encryptionKey.getData(), encryptionKey.getDataSize(),
		CryptoPP::SecByteBlock(reinterpret_cast<const unsigned char *>(DEFAULT_IV), std::strlen(DEFAULT_IV)));
	encryption.ProcessData(data.BytePtr(), data.BytePtr(), data.size());
}

void EncryptionAES::encryptOFB(RawBytes &data)
{

}

void EncryptionAES::decrypt(RawBytes &data)
{
	switch (cipherMode)
	{
		case ECB:
			decryptECB(data);
			break;
		case CBC:
			decryptCBC(data);
			break;
		case CFB:
			decryptCFB(data);
			break;
		case OFB:
			decryptOFB(data);
			break;
	}
}

void EncryptionAES::decryptECB(RawBytes &data)
{

}

void EncryptionAES::decryptCBC(RawBytes &data)
{

}

void EncryptionAES::decryptCFB(RawBytes &data)
{
	CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption decryption(encryptionKey.getData(), encryptionKey.getDataSize(),
		CryptoPP::SecByteBlock(reinterpret_cast<const unsigned char *>(DEFAULT_IV), std::strlen(DEFAULT_IV)));
	decryption.ProcessData(data.BytePtr(), data.BytePtr(), data.size());
}

void EncryptionAES::decryptOFB(RawBytes &data)
{

}
