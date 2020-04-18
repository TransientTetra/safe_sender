#include "../../include/model/encryptable.hpp"
#include "../../include/model/encryption.hpp"

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

RawBytes &Encryptable::getData()
{
	return data;
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

unsigned long Encryptable::getDataSize() const
{
	return data.size();
}

Encryptable::Encryptable()
{

}
