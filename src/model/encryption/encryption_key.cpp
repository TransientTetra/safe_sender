#include "../../../include/model/encryption/encryption_key.hpp"

EncryptionKey::EncryptionKey(const std::string& str)
: Encryptable(str)
{

}

EncryptionKey::EncryptionKey(RawBytes bytes)
: Encryptable(bytes)
{

}

EncryptionKey::EncryptionKey()
{

}

EncryptionKey::~EncryptionKey()
{

}

std::string EncryptionKey::toString()
{
	return data.toString();
}
