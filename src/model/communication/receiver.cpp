#include <iostream>
#include "../../../include/model/communication/receiver.hpp"
#include "../../../include/model/encryption/encryption_aes.hpp"
#include "controller/application.hpp"

Receiver::Receiver(asio::io_service &ioService, unsigned int port)
: Communicator(ioService), acceptor(ioService, tcp::endpoint(tcp::v4(), port))
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
	asio::streambuf buf(size);
	asio::read(socket, buf);
	return RawBytes(asio::buffer_cast<const char*>(buf.data()));
}

void Receiver::listen()
{
	//while (true)
	{
		std::unique_ptr<Encryption> encryption;
		open();
		CipherMode cipherMode = application->getCipherMode();
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
				encryption.reset(new EncryptionAES(receivedPacket.cipherMode));
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
					msg = new TextMessage(receive(receivedPacket.messageSize));
					if (isEncrypted) dynamic_cast<TextMessage*>(msg)->decrypt(*encryption);
					dynamic_cast<TextMessage*>(msg)->print(std::cout);
					break;
				case FILE_MSG:
					msg = new File(receive(receivedPacket.messageSize));
					if (isEncrypted) dynamic_cast<File*>(msg)->decrypt(*encryption);
					//todo fix this once metadata sending is resolved
//					dynamic_cast<File*>(msg)->setMetadata(
//						FileMetadata("test", "txt", receivedPacket.messageSize));
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
	}
}

void Receiver::attachApplication(Application *application)
{
	this->application = application;
}

std::thread Receiver::getListenerThread()
{
	return std::thread(&Receiver::listen, this);
}
