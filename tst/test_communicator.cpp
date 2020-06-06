#include "gtest/gtest.h"
#include "model/communication/communicator.hpp"
TEST(TestCommunicator, testPacketSerialization)
{
	Packet packet;
	packet.responseType = ACCEPT;
	packet.messageType = TXT_MSG;
	packet.messageSize = 697979;
	packet.keySize = 12398567;
	packet.isEncrypted = false;
	packet.cipherMode = CFB;
	strcpy(packet.filename, "file");
	strcpy(packet.extension, "txt");
	strcpy(packet.sessionKey, "fasiodbunvbopasdfub");
	strcpy(packet.iv, "asd;ghasdfp9ubvn");

	Packet copy = packet;
	ASSERT_NE(&packet, &copy);

	ASSERT_EQ(packet.responseType, copy.responseType);
	ASSERT_EQ(packet.messageType, copy.messageType);
	ASSERT_EQ(packet.messageSize, copy.messageSize);
	ASSERT_EQ(packet.keySize, copy.keySize);
	ASSERT_EQ(packet.isEncrypted, copy.isEncrypted);
	ASSERT_EQ(packet.cipherMode, copy.cipherMode);
	ASSERT_EQ(std::string(packet.filename), std::string(copy.filename));
	ASSERT_EQ(std::string(packet.extension), std::string(copy.extension));
	ASSERT_EQ(std::string(packet.sessionKey), std::string(copy.sessionKey));
	ASSERT_EQ(std::string(packet.iv), std::string(copy.iv));
	std::shared_ptr<char> binary = packet.serialize();
	copy.deserialize(binary.get());

	ASSERT_NE(&packet, &copy);

	EXPECT_EQ(packet.responseType, copy.responseType);
	EXPECT_EQ(packet.messageType, copy.messageType);
	EXPECT_EQ(packet.messageSize, copy.messageSize);
	EXPECT_EQ(packet.keySize, copy.keySize);
	EXPECT_EQ(packet.isEncrypted, copy.isEncrypted);
	EXPECT_EQ(packet.cipherMode, copy.cipherMode);
	ASSERT_EQ(std::string(packet.filename), std::string(copy.filename));
	ASSERT_EQ(std::string(packet.extension), std::string(copy.extension));
	ASSERT_EQ(std::string(packet.sessionKey), std::string(copy.sessionKey));
	ASSERT_EQ(std::string(packet.iv), std::string(copy.iv));
}