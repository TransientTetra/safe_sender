#ifndef SAFE_SENDER_ENCRYPTION_RSA_HPP
#define SAFE_SENDER_ENCRYPTION_RSA_HPP


#include "encryption.hpp"
#include <cryptopp/rsa.h>

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

	void generateKeyPair();
};


#endif //SAFE_SENDER_ENCRYPTION_RSA_HPP
