#include "gtest/gtest.h"
#include "model/encryption/encryption_sha_256.hpp"

TEST(TestEncryptionSHA256, testHashing)
{
	EncryptionSHA256 e;
	std::string str1("elo");
	RawBytes data1(reinterpret_cast<const unsigned char *>(str1.c_str()), str1.size());
	ASSERT_EQ(data1.toString(), str1);
	e.encrypt(data1);
	ASSERT_EQ(data1.size(), CryptoPP::SHA256::DIGESTSIZE);
	ASSERT_NE(data1.toString(), str1);
	
	EncryptionSHA256 e2;
	std::string str2("elo");
	RawBytes data2(reinterpret_cast<const unsigned char *>(str2.c_str()), str2.size());
	ASSERT_EQ(data2.toString(), str2);
	e2.encrypt(data2);
	ASSERT_EQ(data2.size(), CryptoPP::SHA256::DIGESTSIZE);
	ASSERT_NE(data2.toString(), str2);
	
	ASSERT_EQ(data2.toString(), data1.toString());
	
	EncryptionSHA256 e3;
	std::string str3("");
	RawBytes data3(reinterpret_cast<const unsigned char *>(str3.c_str()), str3.size());
	ASSERT_EQ(data3.toString(), str3);
	e3.encrypt(data3);
	ASSERT_EQ(data3.size(), CryptoPP::SHA256::DIGESTSIZE);
	ASSERT_NE(data3.toString(), str3);

	EncryptionSHA256 e4;
	std::string str4("Elo");
	RawBytes data4(reinterpret_cast<const unsigned char *>(str4.c_str()), str4.size());
	ASSERT_EQ(data4.toString(), str4);
	e4.encrypt(data4);
	ASSERT_EQ(data4.size(), CryptoPP::SHA256::DIGESTSIZE);
	ASSERT_NE(data4.toString(), str4);

	ASSERT_NE(data2.toString(), data4.toString());
}