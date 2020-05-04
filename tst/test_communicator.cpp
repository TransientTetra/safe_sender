#define BOOST_TEST_DYN_LINK
#include "boost/test/unit_test.hpp"
#include "model/communication/communicator.hpp"

BOOST_AUTO_TEST_SUITE(TestCommunicator)
	BOOST_AUTO_TEST_CASE(testPacketSerialization)
	{
		Packet packet;
		packet.responseType = ACCEPT;
		packet.messageType = TXT_MSG;
		packet.messageSize = 697979;
		packet.keySize = 12398567;
		packet.ivSize = 236234734;
		packet.isEncrypted = false;
		packet.cipherMode = CFB;

		Packet copy = packet;
		BOOST_REQUIRE_NE(&packet, &copy);

		BOOST_REQUIRE_EQUAL(packet.responseType, copy.responseType);
		BOOST_REQUIRE_EQUAL(packet.messageType, copy.messageType);
		BOOST_REQUIRE_EQUAL(packet.messageSize, copy.messageSize);
		BOOST_REQUIRE_EQUAL(packet.keySize, copy.keySize);
		BOOST_REQUIRE_EQUAL(packet.ivSize, copy.ivSize);
		BOOST_REQUIRE_EQUAL(packet.isEncrypted, copy.isEncrypted);
		BOOST_REQUIRE_EQUAL(packet.cipherMode, copy.cipherMode);

		boost::asio::io_service ioService;
		Communicator communicator(ioService);
		char *binary = communicator.serializePacket(packet);
		copy = communicator.deserializePacket(binary);
		delete[] binary;

		BOOST_REQUIRE_NE(&packet, &copy);

		BOOST_CHECK_EQUAL(packet.responseType, copy.responseType);
		BOOST_CHECK_EQUAL(packet.messageType, copy.messageType);
		BOOST_CHECK_EQUAL(packet.messageSize, copy.messageSize);
		BOOST_CHECK_EQUAL(packet.keySize, copy.keySize);
		BOOST_CHECK_EQUAL(packet.ivSize, copy.ivSize);
		BOOST_CHECK_EQUAL(packet.isEncrypted, copy.isEncrypted);
		BOOST_CHECK_EQUAL(packet.cipherMode, copy.cipherMode);
	}
BOOST_AUTO_TEST_SUITE_END()