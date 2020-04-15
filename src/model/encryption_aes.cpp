#include "../../include/model/encryption_aes.hpp"
#include <ostream>
#include <crypto++/aes.h>

RawBytes EncryptionAES::encrypt(const RawBytes &data)
{

	return RawBytes("lol");
}

EncryptionAES::EncryptionAES(CipherMode cipherMode)
{
	this->cipherMode;
}

void EncryptionAES::setEncryptionKey(std::string str)
{
	key.setKey(str);
}
