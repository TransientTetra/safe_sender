#include "gtest/gtest.h"
#include "model/encryption/encryption_aes.hpp"
TEST(TestEncryptionAES, testEncryptionKeyInteraction)
{}

TEST(TestEncryptionAES, testIVInteraction)
{}

TEST(TestEncryptionAES, testStringEncryptionCFB)
{
	std::vector<RawBytes> rawBytes;
	std::string testString1 = "";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString1.c_str()), testString1.size()));
	std::string testString2 = "\0";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString2.c_str()), testString2.size()));
	std::string testString3 = "\n";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString3.c_str()), testString3.size()));
	std::string testString4 = "ddddddf;awseiugnbpzcvij;dasjidfoadpsjfioaspnbgpqaewrn8giunfjpasdifjcn";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString4.c_str()), testString4.size()));
	std::string testString5 = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString5.c_str()), testString5.size()));
	std::string testString6 = "\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString6.c_str()), testString6.size()));
	std::string testString7 = "dddddd\nf;awseiugnbpz\ncvij;dasjidfoa\0dpsjfispnbgpqaewrn8giunf\0jpasdifjcn";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString7.c_str()), testString7.size()));

	EncryptionAES encryption(CFB);
	EncryptionKey key("6969696969696969");
	encryption.setEncryptionKey(key);

	for (RawBytes b : rawBytes)
	{
		std::string nominalValue = b.toString();
		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_EQ(b.toString(), nominalValue);

		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_EQ(b.toString(), nominalValue);

		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_EQ(b.toString(), nominalValue);
	}
}

TEST(TestEncryptionAES, testStringEncryptionCBC)
{
	std::vector<RawBytes> rawBytes;
	std::string testString1 = "";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString1.c_str()), testString1.size()));
	std::string testString2 = "\0";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString2.c_str()), testString2.size()));
	std::string testString3 = "\n";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString3.c_str()), testString3.size()));
	std::string testString4 = "ddddddf;awseiugnbpzcvij;dasjidfoadpsjfioaspnbgpqaewrn8giunfjpasdifjcn";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString4.c_str()), testString4.size()));
	std::string testString5 = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString5.c_str()), testString5.size()));
	std::string testString6 = "\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString6.c_str()), testString6.size()));
	std::string testString7 = "dddddd\nf;awseiugnbpz\ncvij;dasjidfoa\0dpsjfispnbgpqaewrn8giunf\0jpasdifjcn";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString7.c_str()), testString7.size()));

	EncryptionAES encryption(CBC);
	EncryptionKey key("6969696969696969");
	encryption.setEncryptionKey(key);

	for (RawBytes b : rawBytes)
	{
		std::string nominalValue = b.toString();
		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_EQ(b.toString(), nominalValue);

		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_EQ(b.toString(), nominalValue);

		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_EQ(b.toString(), nominalValue);
	}
}

TEST(TestEncryptionAES, testStringEncryptionOFB)
{
	std::vector<RawBytes> rawBytes;
	std::string testString1 = "";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString1.c_str()), testString1.size()));
	std::string testString2 = "\0";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString2.c_str()), testString2.size()));
	std::string testString3 = "\n";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString3.c_str()), testString3.size()));
	std::string testString4 = "ddddddf;awseiugnbpzcvij;dasjidfoadpsjfioaspnbgpqaewrn8giunfjpasdifjcn";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString4.c_str()), testString4.size()));
	std::string testString5 = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString5.c_str()), testString5.size()));
	std::string testString6 = "\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString6.c_str()), testString6.size()));
	std::string testString7 = "dddddd\nf;awseiugnbpz\ncvij;dasjidfoa\0dpsjfispnbgpqaewrn8giunf\0jpasdifjcn";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString7.c_str()), testString7.size()));

	EncryptionAES encryption(OFB);
	EncryptionKey key("6969696969696969");
	encryption.setEncryptionKey(key);

	for (RawBytes b : rawBytes)
	{
		std::string nominalValue = b.toString();
		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_EQ(b.toString(), nominalValue);

		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_EQ(b.toString(), nominalValue);

		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_EQ(b.toString(), nominalValue);
	}
}

TEST(TestEncryptionAES, testStringEncryptionECB)
{
	std::vector<RawBytes> rawBytes;
	std::string testString1 = "";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString1.c_str()), testString1.size()));
	std::string testString2 = "\0";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString2.c_str()), testString2.size()));
	std::string testString3 = "\n";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString3.c_str()), testString3.size()));
	std::string testString4 = "ddddddf;awseiugnbpzcvij;dasjidfoadpsjfioaspnbgpqaewrn8giunfjpasdifjcn";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString4.c_str()), testString4.size()));
	std::string testString5 = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString5.c_str()), testString5.size()));
	std::string testString6 = "\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString6.c_str()), testString6.size()));
	std::string testString7 = "dddddd\nf;awseiugnbpz\ncvij;dasjidfoa\0dpsjfispnbgpqaewrn8giunf\0jpasdifjcn";
	rawBytes.emplace_back(
		RawBytes(reinterpret_cast<const unsigned char*>(testString7.c_str()), testString7.size()));

	EncryptionAES encryption(ECB);
	EncryptionKey key("6969696969696969");
	encryption.setEncryptionKey(key);

	for (RawBytes b : rawBytes)
	{
		std::string nominalValue = b.toString();
		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_EQ(b.toString(), nominalValue);

		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_EQ(b.toString(), nominalValue);

		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.encrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_NO_THROW(encryption.decrypt(b));
		ASSERT_EQ(b.toString(), nominalValue);
	}
}