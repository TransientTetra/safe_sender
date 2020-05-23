#include "../../../include/model/encryption/encryption.hpp"

void Encryption::setEncryptionKey(EncryptionKey &key)
{
	encryptionKey = key;
}

const EncryptionKey Encryption::getEncryptionKey() const
{
	return encryptionKey;
}

float Encryption::getProgress()
{
	return 0;
}
