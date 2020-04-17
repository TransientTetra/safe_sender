#include "../../include/model/encryption.hpp"

void Encryption::setEncryptionKey(RawBytes &bytes)
{
	encryptionKey = bytes;
}

void Encryption::setEncryptionKey(std::string str)
{
	encryptionKey = RawBytes(str);
}

void Encryption::setIV(std::string str)
{
	initializationVector = RawBytes(str);
}

void Encryption::setIV(RawBytes &bytes)
{
	initializationVector = bytes;
}
