#include "model/encryption/encryption_sha_256.hpp"

void EncryptionSHA256::encrypt(RawBytes &data)
{
	byte digest[CryptoPP::SHA256::DIGESTSIZE];
	CryptoPP::SHA256().CalculateDigest(digest, data.BytePtr(), data.size());
	data.Assign(digest, CryptoPP::SHA256::DIGESTSIZE);
}

void EncryptionSHA256::decrypt(RawBytes &data)
{

}
