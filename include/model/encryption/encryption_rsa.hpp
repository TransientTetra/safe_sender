#ifndef SAFE_SENDER_ENCRYPTION_RSA_HPP
#define SAFE_SENDER_ENCRYPTION_RSA_HPP


#include "encryption.hpp"
#include <cryptopp/rsa.h>
#include <model/communication/communicator.hpp>

class EncryptionRSA : public Encryption
{
private:
	CryptoPP::RSA::PrivateKey privateKey;
	CryptoPP::RSA::PublicKey publicKey;
protected:
public:
	void encrypt(RawBytes &data) override;
	void decrypt(RawBytes &data) override;

	const CryptoPP::RSA::PrivateKey &getPrivateKey() const;

	void setPrivateKey(const CryptoPP::RSA::PrivateKey &privateKey);

	const CryptoPP::RSA::PublicKey &getPublicKey() const;

	void setPublicKey(const CryptoPP::RSA::PublicKey &publicKey);

	void encryptKeysToFile(std::string path, EncryptionKey& key);
	bool decryptKeysFromFile(std::string path, EncryptionKey& key);

	void generateKeyPair();
};


#endif //SAFE_SENDER_ENCRYPTION_RSA_HPP
