#include <iostream>
#include "../../../include/model/communication/receiver.hpp"
#include "../../../include/model/initialization_vector.hpp"
#include "../../../include/model/encryption/encryption_key.hpp"
#include "../../../include/model/encryption/encryption_aes.hpp"
#include "../../../include/model/text_message.hpp"
#include "../../../include/model/file.hpp"

Receiver::Receiver(boost::asio::io_service &ioService, unsigned int port)
: Communicator(ioService),
acceptor(ioService, boost::asio::ip::tcp::tcp::endpoint(boost::asio::ip::tcp::tcp::v4(), port))
{
	this->port = port;
	connected = false;
}

void Receiver::open()
{
	acceptor.accept(socket);
}

RawBytes Receiver::receive(unsigned long size)
{
	boost::asio::streambuf buf(size);
	boost::asio::read(socket, buf);
	return RawBytes(boost::asio::buffer_cast<const char*>(buf.data()));
}

void Receiver::listenAndReceive()
{
	//while (true)
	{
		Encryption *encryption;
		open();
		//todo cipher mode choosing
		Packet receivedPacket = receivePacket();
		bool isEncrypted = receivedPacket.isEncrypted;
		//todo ask user if accepts here and send appropriate signal
		Packet responsePacket;
		responsePacket.responseType = ACCEPT;
		sendPacket(responsePacket);
		try
		{
			if (isEncrypted)
			{
				encryption = new EncryptionAES(receivedPacket.cipherMode);
				EncryptionKey aesKey = receive(receivedPacket.keySize);
				InitializationVector iv = receive(receivedPacket.ivSize);
				encryption->setEncryptionKey(aesKey);
				encryption->setIV(iv);
			}
			if (receivedPacket.messageType == FILE_MSG)
			{
				//todo handle file metadata receiving
			}

			Sendable *msg;
			switch (receivedPacket.messageType)
			{
				case TXT_MSG:
					msg = new TextMessage(receivedPacket.messageSize);
					if (isEncrypted) dynamic_cast<TextMessage*>(msg)->decrypt(*encryption);
					dynamic_cast<TextMessage*>(msg)->print(std::cout);
					break;
				case FILE_MSG:
					msg = new File(receivedPacket.messageSize);
					if (isEncrypted) dynamic_cast<File*>(msg)->decrypt(*encryption);
					//todo fix this once metadata sending is resolved
					dynamic_cast<File*>(msg)->setMetadata(
						FileMetadata("test", "txt", receivedPacket.messageSize));
					//todo handle path getting
					dynamic_cast<File*>(msg)->save("/home/bsk/Temp/");
					break;
				default:
					break;
			}
			//delete msg;
		}
		catch (std::exception &e)
		{
			std::cerr << "Error while receiving data\n";
		}
		if (isEncrypted) delete encryption;
	}
}
