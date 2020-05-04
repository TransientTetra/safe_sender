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
		open();
		//todo cipher mode choosing
		EncryptionAES encryption(CFB);
		MessageType type = receiveSignal<MessageType>();
		//todo ask user if accepts here and send appropriate signal
		sendSignal(ACCEPT);
		try
		{
			bool isEncrypted = receiveSignal<bool>();
			if (isEncrypted)
			{
				unsigned long keySize = receiveSignal<unsigned long>();
				EncryptionKey aesKey = receive(keySize);
				unsigned long ivSize = receiveSignal<unsigned long>();
				InitializationVector iv = receive(ivSize);
				encryption.setEncryptionKey(aesKey);
				encryption.setIV(iv);
			}
			if (type == FILE_MSG)
			{
				//todo handle file metadata sending
			}
			unsigned long size = receiveSignal<unsigned long>();

			Sendable *msg;
			switch (type)
			{
				case TXT_MSG:
					msg = new TextMessage(receive(size));
					if (isEncrypted) dynamic_cast<TextMessage*>(msg)->decrypt(encryption);
					dynamic_cast<TextMessage*>(msg)->print(std::cout);
					break;
				case FILE_MSG:
					msg = new File(receive(size));
					if (isEncrypted) dynamic_cast<File*>(msg)->decrypt(encryption);
					//todo fix this once metadata sending is resolved
					dynamic_cast<File*>(msg)->setMetadata(FileMetadata("test", "txt", size));
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
