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
		Receiver receiver(io_service, port);
		while(1)
		{
			receiver.open();
			receiver.listenAndReceive();
		}
	}
	else
	{
		EncryptionKey key("6969696969696969");
		InitializationVector iv("69696969");
		EncryptionAES encryptionAes(CFB);
		encryptionAes.setEncryptionKey(key);
		encryptionAes.setIV(iv);
		TextMessage str("no siemano");
		File file("/home/mkj/Temp/New");
		file.encrypt(encryptionAes);
		str.encrypt(encryptionAes);
		//connect can throw Connection refused if there's no server to connect to or sth
		Sender sender(io_service, ip_to_send_to, port);
		sender.connect();
		//sender.sendTxtMsg(str, key, iv, true);
		sender.sendFile(file, key, iv, true);
	}
	return 0;
}