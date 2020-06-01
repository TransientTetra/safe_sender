#include "model/encryption/encryption_rsa.hpp"
#include <cryptopp/osrng.h>
#include <constants.hpp>

void EncryptionRSA::generateKeyPair()
{
	CryptoPP::AutoSeededRandomPool rng;
	CryptoPP::InvertibleRSAFunction params;
	params.GenerateRandomWithKeySize(rng, DEFAULT_RSA_KEY_SIZE);

	privateKey = CryptoPP::RSA::PrivateKey(params);
	publicKey = CryptoPP::RSA::PublicKey(params);
}

const CryptoPP::RSA::PrivateKey &EncryptionRSA::getPrivateKey() const
{
	return privateKey;
}

void EncryptionRSA::setPrivateKey(const CryptoPP::RSA::PrivateKey &privateKey)
{
	EncryptionRSA::privateKey = privateKey;
}

const CryptoPP::RSA::PublicKey &EncryptionRSA::getPublicKey() const
{
	return publicKey;
}

void EncryptionRSA::setPublicKey(const CryptoPP::RSA::PublicKey &publicKey)
{
	EncryptionRSA::publicKey = publicKey;
}

void EncryptionRSA::encrypt(RawBytes &data)
{
	CryptoPP::AutoSeededRandomPool rng;
	CryptoPP::RSAES_OAEP_SHA_Encryptor e(publicKey);

	std::string encrypted;
	CryptoPP::StringSource ss1(data.toString(), true,
		new CryptoPP::PK_EncryptorFilter(rng, e, new CryptoPP::StringSink(encrypted)));
	data.Assign(reinterpret_cast<const unsigned char *>(encrypted.c_str()), encrypted.size());
}

void EncryptionRSA::decrypt(RawBytes &data)
{
	CryptoPP::AutoSeededRandomPool rng;
	CryptoPP::RSAES_OAEP_SHA_Decryptor d(privateKey);

	std::string decrypted;
	CryptoPP::StringSource ss2(data.toString(), true,
		new CryptoPP::PK_DecryptorFilter(rng, d, new CryptoPP::StringSink(decrypted)));
	data.Assign(reinterpret_cast<const unsigned char *>(decrypted.c_str()), decrypted.size());
}
