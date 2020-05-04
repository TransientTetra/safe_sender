#define BOOST_TEST_MODULE tst
#include "boost/test/unit_test.hpp"
#include "model/encryption/encryption_aes.hpp"

BOOST_AUTO_TEST_SUITE(TestEncryptionAES)
	BOOST_AUTO_TEST_CASE(testEncryptionKeyInteraction)
	{}
	BOOST_AUTO_TEST_CASE(testIVInteraction)
	{}
	BOOST_AUTO_TEST_CASE(testStringEncryptionCFB)
	{
		std::vector<RawBytes> rawBytes;
		std::string testString1 = "";
		rawBytes.emplace_back(testString1);
		std::string testString2 = "\0";
		rawBytes.emplace_back(testString2);
		std::string testString3 = "\n";
		rawBytes.emplace_back(testString3);
		std::string testString4 = "ddddddf;awseiugnbpzcvij;dasjidfoadpsjfioaspnbgpqaewrn8giunfjpasdifjcn";
		rawBytes.emplace_back(testString4);
		std::string testString5 = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		rawBytes.emplace_back(testString5);
		std::string testString6 = "\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n\0\n";
		rawBytes.emplace_back(testString6);
		std::string testString7 = "dddddd\nf;awseiugnbpz\ncvij;dasjidfoa\0dpsjfispnbgpqaewrn8giunf\0jpasdifjcn";
		rawBytes.emplace_back(testString7);

		EncryptionAES encryption(CFB);
		EncryptionKey key("6969696969696969");
		InitializationVector iv("0");
		encryption.setEncryptionKey(key);
		encryption.setIV(iv);

		for (RawBytes b : rawBytes)
		{
			std::string nominalValue = b.toString();
			BOOST_REQUIRE_NO_THROW(encryption.encrypt(b));
			BOOST_REQUIRE_NO_THROW(encryption.decrypt(b));
			BOOST_REQUIRE_EQUAL(b.toString(), nominalValue);

			BOOST_REQUIRE_NO_THROW(encryption.encrypt(b));
			BOOST_REQUIRE_NO_THROW(encryption.encrypt(b));
			BOOST_REQUIRE_NO_THROW(encryption.decrypt(b));
			BOOST_REQUIRE_NO_THROW(encryption.decrypt(b));
			BOOST_REQUIRE_EQUAL(b.toString(), nominalValue);

			BOOST_REQUIRE_NO_THROW(encryption.encrypt(b));
			BOOST_REQUIRE_NO_THROW(encryption.encrypt(b));
			BOOST_REQUIRE_NO_THROW(encryption.encrypt(b));
			BOOST_REQUIRE_NO_THROW(encryption.encrypt(b));
			BOOST_REQUIRE_NO_THROW(encryption.decrypt(b));
			BOOST_REQUIRE_NO_THROW(encryption.decrypt(b));
			BOOST_REQUIRE_NO_THROW(encryption.decrypt(b));
			BOOST_REQUIRE_NO_THROW(encryption.decrypt(b));
			BOOST_REQUIRE_EQUAL(b.toString(), nominalValue);
		}
	}
BOOST_AUTO_TEST_SUITE_END()