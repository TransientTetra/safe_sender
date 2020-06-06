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

	void saveKeysToFile(std::string privPath, std::string publPath);
	void loadKeysFromFile(std::string privPath, std::string publPath);
protected:
public:
	void encrypt(RawBytes &data) override;
	void decrypt(RawBytes &data) override;

	const CryptoPP::RSA::PrivateKey &getPrivateKey() const;

	void setPrivateKey(const CryptoPP::RSA::PrivateKey &privateKey);

	CryptoPP::RSA::PublicKey &getPublicKey();

	void setPublicKey(const CryptoPP::RSA::PublicKey &publicKey);

	void savePublicKey(std::string path);
	void loadPublicKey(std::string path);

	void encryptKeysToFile(std::string privPath, std::string publPath, EncryptionKey& key);
	bool decryptKeysFromFile(std::string privPath, std::string publPath, EncryptionKey& key);

	void generateKeyPair();
};


#endif //SAFE_SENDER_ENCRYPTION_RSA_HPP
