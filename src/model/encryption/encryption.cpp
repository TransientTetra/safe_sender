#include "../../../include/model/encryption/encryption.hpp"

void Encryption::setEncryptionKey(EncryptionKey &key)
{
	encryptionKey = key;
}

const EncryptionKey& Encryption::getEncryptionKey() const
{
	return encryptionKey;
}

float Encryption::getProgress()
{
	return 0;
}

void Encryption::setIV(const char *arr)
{
	iv = std::string(arr);
}

CipherMode Encryption::getCipherMode() const
{
	return cipherMode;
}

const std::string &Encryption::getIV() const
{
	return iv;
}
