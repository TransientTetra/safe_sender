#include "../../include/model/encryption.hpp"

void Encryption::setEncryptionKey(EncryptionKey &key)
{
	encryptionKey = key;
}

void Encryption::setIV(InitializationVector &iv)
{
	initializationVector = iv;
}

const EncryptionKey Encryption::getEncryptionKey() const
{
	return encryptionKey;
}

const InitializationVector Encryption::getInitializationVector() const
{
	return initializationVector;
}
