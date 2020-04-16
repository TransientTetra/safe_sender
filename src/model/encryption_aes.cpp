#include "../../include/model/encryption_aes.hpp"
#include <ostream>
#include <crypto++/aes.h>
#include <crypto++/modes.h>

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

void EncryptionAES::setEncryptionKey(std::string str)
{
	encryptionKey = RawBytes(str);
}

void EncryptionAES::encryptECB(RawBytes &data)
{

}

void EncryptionAES::encryptCBC(RawBytes &data)
{

}

void EncryptionAES::encryptCFB(RawBytes &data)
{
	CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption encryption(encryptionKey.toSecByteBlock(),
		encryptionKey.getSize(), initializationVector.toSecByteBlock());
	byte *dataPtr = reinterpret_cast<byte *>(data.getVectorPtr());
	encryption.ProcessData(dataPtr, dataPtr, data.getSize());
}

void EncryptionAES::encryptOFB(RawBytes &data)
{

}

void EncryptionAES::setIV(std::string str)
{
	initializationVector = RawBytes(str);
}

void EncryptionAES::setEncryptionKey(RawBytes &bytes)
{
	encryptionKey = bytes;
}

void EncryptionAES::setIV(RawBytes &bytes)
{
	initializationVector = bytes;
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
	CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption decryption(encryptionKey.toSecByteBlock(),
								 encryptionKey.getSize(), initializationVector.toSecByteBlock());
	byte *dataPtr = reinterpret_cast<byte *>(data.getVectorPtr());
	decryption.ProcessData(dataPtr, dataPtr, data.getSize());
}

void EncryptionAES::decryptOFB(RawBytes &data)
{

}
