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

	Packet copy = packet;
	ASSERT_NE(&packet, &copy);

	ASSERT_EQ(packet.responseType, copy.responseType);
	ASSERT_EQ(packet.messageType, copy.messageType);
	ASSERT_EQ(packet.messageSize, copy.messageSize);
	ASSERT_EQ(packet.keySize, copy.keySize);
	ASSERT_EQ(packet.isEncrypted, copy.isEncrypted);
	ASSERT_EQ(packet.cipherMode, copy.cipherMode);
	std::unique_ptr<char> binary;
	binary.reset(Communicator::serializePacket(packet));
	copy = Communicator::deserializePacket(binary.get());

	ASSERT_NE(&packet, &copy);

	EXPECT_EQ(packet.responseType, copy.responseType);
	EXPECT_EQ(packet.messageType, copy.messageType);
	EXPECT_EQ(packet.messageSize, copy.messageSize);
	EXPECT_EQ(packet.keySize, copy.keySize);
	EXPECT_EQ(packet.isEncrypted, copy.isEncrypted);
	EXPECT_EQ(packet.cipherMode, copy.cipherMode);
}