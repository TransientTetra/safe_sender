#include "model/encryption/encryption_rsa.hpp"
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>
#include <constants.hpp>
#include <cryptopp/modes.h>
#include <model/file.hpp>
#include <model/encryption/encryption_aes.hpp>
#include <filesystem>
#include <model/encryption/encryption_sha_256.hpp>

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
	try
	{
		CryptoPP::AutoSeededRandomPool rng;
		CryptoPP::RSAES_OAEP_SHA_Decryptor d(privateKey);

		std::string decrypted;
		CryptoPP::StringSource ss2(data.toString(), true,
					   new CryptoPP::PK_DecryptorFilter(rng, d, new CryptoPP::StringSink(decrypted)));
		data.Assign(reinterpret_cast<const unsigned char *>(decrypted.c_str()), decrypted.size());
	}
	catch (std::exception e)
	{
		CryptoPP::AutoSeededRandomPool rnd;
		RawBytes temp(DEFAULT_SESSION_KEY_SIZE);
		EncryptionSHA256 sha;
		sha.encrypt(temp);
		data = temp;
	}
}

void EncryptionRSA::encryptKeysToFile(std::string privPath, std::string publPath, EncryptionKey& key)
{
	{
		CryptoPP::FileSink output(privPath.c_str(), true);
		privateKey.DEREncode(output);
		CryptoPP::FileSink output2(publPath.c_str(), true);
		publicKey.DEREncode(output2);
	}
	File priv(privPath);
	File publ(publPath);
	EncryptionAES encryption(CBC);
	encryption.setEncryptionKey(key);
	encryption.setIV(DEFAULT_IV);
	priv.encrypt(encryption);
	publ.encrypt(encryption);
	priv.save(privPath);
	publ.save(publPath);
}

bool EncryptionRSA::decryptKeysFromFile(std::string privPath, std::string publPath, EncryptionKey &key)
{
	try
	{
		File priv(privPath);
		File publ(publPath);
		EncryptionAES encryption(CBC);
		encryption.setEncryptionKey(key);
		encryption.setIV(DEFAULT_IV);
		priv.decrypt(encryption);
		publ.decrypt(encryption);
		priv.save(privPath);
		publ.save(publPath);
		{
			CryptoPP::FileSource input(privPath.c_str(), true);
			privateKey.BERDecode(input);
			CryptoPP::FileSource input2(publPath.c_str(), true);
			publicKey.BERDecode(input2);
		}
		priv.encrypt(encryption);
		publ.encrypt(encryption);
		priv.save(privPath);
		publ.save(publPath);
		return true;
	}
	catch (std::exception e)
	{
		//creating mismatched key pair
		generateKeyPair();
		CryptoPP::RSA::PublicKey temp = getPublicKey();
		generateKeyPair();
		setPublicKey(temp);
		return false;
	}
}
