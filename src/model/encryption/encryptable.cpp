#include "../../../include/model/encryption/encryptable.hpp"
#include "../../../include/model/encryption/encryption.hpp"

Encryptable::Encryptable()
{

}

Encryptable::Encryptable(const std::string& str)
{
	encrypted = false;
	data = RawBytes(str);
}

Encryptable::Encryptable(RawBytes &bytes)
{
	encrypted = false;
	data = bytes;
}

void Encryptable::encrypt(Encryption &encryption)
{
	encrypted = true;
	encryption.encrypt(data);
}

void Encryptable::decrypt(Encryption &encryption)
{
	encrypted = false;
	encryption.decrypt(data);
}

bool Encryptable::isEncrypted()
{
	return encrypted;
}

