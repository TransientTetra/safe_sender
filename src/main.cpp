#include <iostream>
#include <string>
#include "../include/controller/application.hpp"
#include "../include/model/text_message.hpp"
#include "../include/model/encryption/encryption_aes.hpp"
#include "../include/model/raw_bytes.hpp"
#include "../include/model/file.hpp"
#include "../include/model/communication/sender.hpp"
#include "../include/model/communication/receiver.hpp"
#include <crypto++/randpool.h>
#include <crypto++/aes.h>
#include <crypto++/osrng.h>
#include <boost/asio.hpp>

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		std::cerr << "safe_sender <ip> <is_server ? 1 : 0>\n";
		return 1;
	}
	std::string ip_to_send_to = argv[1];
	unsigned int port = 1234;
	bool is_server = *argv[2] != '0';

	boost::asio::io_service io_service;
	if (is_server)
	{
		Receiver receiver(io_service, 1234);
		receiver.open();
		if (receiver.receiveSignal<MessageType>() == KEY)
		{
			receiver.sendSignal<ResponseType>(ACCEPT);
		}
		else
		{
			receiver.sendSignal<ResponseType>(REJECT);
			return 15;
		}
		unsigned long size = receiver.receiveSignal<unsigned long>();
		EncryptionKey key(receiver.receive(size));
		if (receiver.receiveSignal<MessageType>() == IV)
		{
			receiver.sendSignal<ResponseType>(ACCEPT);
		}
		else
		{
			receiver.sendSignal<ResponseType>(REJECT);
			return 15;
		}
		size = receiver.receiveSignal<unsigned long>();
		InitializationVector iv(receiver.receive(size));

		EncryptionAES encryptionAes(CFB);
		encryptionAes.setEncryptionKey(key);
		encryptionAes.setIV(iv);

		if (receiver.receiveSignal<MessageType>() == TXT_MSG)
		{
			receiver.sendSignal<ResponseType>(ACCEPT);
		}
		else
		{
			receiver.sendSignal<ResponseType>(REJECT);
			return 15;
		}
		size = receiver.receiveSignal<unsigned long>();
		TextMessage msg(receiver.receive(size));
		std::cout << msg.getData().toString() << '\n';
		msg.decrypt(encryptionAes);
		std::cout << msg.getData().toString() << '\n';
	}
	else
	{
		EncryptionKey key("6969696969696969");
		InitializationVector iv("69696969");
		EncryptionAES encryptionAes(CFB);
		encryptionAes.setEncryptionKey(key);
		encryptionAes.setIV(iv);
		TextMessage str("no siemano");
		str.encrypt(encryptionAes);
		//connect can throw Connection refused if there's no server to connect to or sth
		Sender sender(io_service, ip_to_send_to, port);
		sender.connect();
		sender.sendSignal<MessageType>(KEY);

		if (sender.receiveSignal<ResponseType>() == ACCEPT)
		{
			sender.sendSignal(key.getDataSize());
			sender.send(key);
		}
		sender.sendSignal(IV);

		if (sender.receiveSignal<ResponseType>() == ACCEPT)
		{
			sender.sendSignal(iv.getDataSize());
			sender.send(iv);
		}
		sender.sendSignal(TXT_MSG);

		if (sender.receiveSignal<ResponseType>() == ACCEPT)
		{
			sender.sendSignal(str.getDataSize());
			sender.send(str);
		}
	}
	return 0;
}