#include <iostream>
#include "../../../include/model/communication/receiver.hpp"
#include "../../../include/model/encryption/encryption_aes.hpp"
#include "controller/application.hpp"

Receiver::Receiver(unsigned int port)
: Communicator()
{
	this->port = port;
	connected = false;
}

void Receiver::open()
{
//	acceptor.accept(socket);
}

RawBytes Receiver::receive(unsigned long size)
{
	//todo
//	boost::asio::streambuf buf(size);
//	boost::asio::read(socket, buf);
//	return RawBytes(boost::asio::buffer_cast<const char*>(buf.data()));
return RawBytes();
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

			//todo make msg smart ptr
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
