#include "gtest/gtest.h"
#include "model/encryption/encryption_rsa.hpp"

TEST(TestEncryptionRSA, testEncryptionDecryption)
{
	EncryptionRSA e;
	e.generateKeyPair();
	std::string str("elo");
	RawBytes data(reinterpret_cast<const unsigned char *>(str.c_str()), str.size());
	ASSERT_EQ(data.toString(), str);
	e.encrypt(data);
	ASSERT_NE(data.toString(), str);
	e.decrypt(data);
	ASSERT_EQ(data.toString(), str);
}