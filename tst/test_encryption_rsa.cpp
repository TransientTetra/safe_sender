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

TEST(TestEncryptionRSA, testPacketEncryption)
{
	Packet packet;
	packet.messageType = TXT_MSG;
	packet.responseType = REJECT;
	packet.cipherMode = ECB;
	packet.messageSize = 323;
	packet.keySize = 6969;
	packet.isEncrypted = false;
	strcpy(packet.filename, "file");
	strcpy(packet.extension, "txt");
	strcpy(packet.sessionKey, "fasiodbunvbopasdfub");
	strcpy(packet.iv, "asd;ghasdfp9ubvn");
	
	Packet packet2;

	EncryptionRSA e;
	e.generateKeyPair();
	RawBytes temp(reinterpret_cast<const unsigned char *>(packet.serialize().get()), sizeof(Packet));
	e.encrypt(temp);
	e.decrypt(temp);
	packet2.deserialize(reinterpret_cast<const char *>(temp.BytePtr()));
	ASSERT_EQ(packet.messageType, packet2.messageType);
	ASSERT_EQ(packet.responseType, packet2.responseType);
	ASSERT_EQ(packet.cipherMode, packet2.cipherMode);
	ASSERT_EQ(packet.keySize, packet2.keySize);
	ASSERT_EQ(packet.isEncrypted, packet2.isEncrypted);
	ASSERT_EQ(std::string(packet.filename), std::string(packet2.filename));
	ASSERT_EQ(std::string(packet.extension), std::string(packet2.extension));
	ASSERT_EQ(std::string(packet.sessionKey), std::string(packet2.sessionKey));
	ASSERT_EQ(std::string(packet.iv), std::string(packet2.iv));
}