#include "../../include/model/encryption_aes.hpp"
#include <ostream>
#include <crypto++/aes.h>

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
	data = RawBytes("lol");
}

void EncryptionAES::encryptOFB(RawBytes &data)
{

}
