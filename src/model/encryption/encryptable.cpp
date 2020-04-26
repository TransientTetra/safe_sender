#include "../../../include/model/encryption/encryptable.hpp"
#include "../../../include/model/encryption/encryption.hpp"

Encryptable::Encryptable()
{

}

Encryptable::Encryptable(const std::string& str)
{
	isEncrypted = false;
	data = RawBytes(str);
}

Encryptable::Encryptable(RawBytes &bytes)
{
	isEncrypted = false;
	data = bytes;
}

void Encryptable::encrypt(Encryption &encryption)
{
	isEncrypted = true;
	encryption.encrypt(data);
}

void Encryptable::decrypt(Encryption &encryption)
{
	isEncrypted = false;
	encryption.decrypt(data);
}

