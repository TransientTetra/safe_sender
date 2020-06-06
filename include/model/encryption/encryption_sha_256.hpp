#ifndef SAFE_SENDER_ENCRYPTION_SHA_256_HPP
#define SAFE_SENDER_ENCRYPTION_SHA_256_HPP


#include "encryption.hpp"
#include <cryptopp/sha.h>

class EncryptionSHA256 : public Encryption
{
private:
protected:
public:
	void encrypt(RawBytes &data) override;
	void decrypt(RawBytes &data) override;
};


#endif //SAFE_SENDER_ENCRYPTION_SHA_256_HPP
