#include <iostream>
#include <model/encryption/encryption_aes.hpp>
#include "model/communication/session.hpp"

Session::Session(tcp::socket &&socket, Application* application)
: Communicator(std::move(socket))
{
	this->application = application;
}

void Session::start()
{
	handleIncoming(receivePacket());
}


RawBytes Session::receive(unsigned long size)
{
	asio::streambuf buf(size);
	asio::read(socket, buf);
	return RawBytes(asio::buffer_cast<const char*>(buf.data()));
}

void Session::handleIncoming(Packet packet)
{
	std::unique_ptr<Encryption> encryption;
	bool isEncrypted = packet.isEncrypted;
	//todo ask user if accepts here and send appropriate signal
	Packet responsePacket;
	responsePacket.responseType = ACCEPT;
	sendPacket(responsePacket);
	try
	{
		if (isEncrypted)
		{
			encryption.reset(new EncryptionAES(packet.cipherMode));
			EncryptionKey aesKey = receive(packet.keySize);
			InitializationVector iv = receive(packet.ivSize);
			encryption->setEncryptionKey(aesKey);
			encryption->setIV(iv);
		}
		if (packet.messageType == FILE_MSG)
		{
			//todo handle file metadata receiving
		}
		
		std::unique_ptr<DataContainer> msg;
		switch (packet.messageType)
		{
			case TXT_MSG:
				msg.reset(new TextMessage(receive(packet.messageSize)));
				if (isEncrypted) dynamic_cast<TextMessage*>(msg.get())->decrypt(*encryption);
				//todo display msg
				dynamic_cast<TextMessage*>(msg.get())->print(std::cout);
				break;
			case FILE_MSG:
				msg.reset(new File(receive(packet.messageSize)));
				if (isEncrypted) dynamic_cast<File*>(msg.get())->decrypt(*encryption);
				//todo fix this once metadata sending is resolved
				//					dynamic_cast<File*>(msg)->setMetadata(
				//						FileMetadata("test", "txt", packet.messageSize));
				//todo handle path getting
				dynamic_cast<File*>(msg.get())->save("/home/bsk/Temp/");
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
