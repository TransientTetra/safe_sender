#include <iostream>
#include "controller/application.hpp"
#include "constants.hpp"
#include "view/main_frame.hpp"
#include "model/communication/sender.hpp"
#include "model/communication/receiver.hpp"
#include "model/encryption/encryption_aes.hpp"

// Main code
int main(int argc, char** argv)
{
	Application application(DEFAULT_WINDOW_TITLE);
	application.run();
	return 0;
	if (argc < 3)
	{
		std::cerr << "safe_sender <ip> <is_server ? 1 : 0>\n";
		return 1;
	}
	std::string ip_to_send_to = argv[1];
	bool is_server = *argv[2] != '0';

	boost::asio::io_service io_service;
	if (is_server)
	{
		Receiver receiver(io_service, DEFAULT_PORT);
		std::thread receiverThread(&Receiver::listenAndReceive, &receiver);
		receiverThread.join();
	}
	else
	{
		EncryptionKey key("6969696969696969");
		InitializationVector iv("69696969");
		EncryptionAES encryptionAes(CFB);
		encryptionAes.setEncryptionKey(key);
		encryptionAes.setIV(iv);
		TextMessage str("no siemano");
		//File file("/home/mkj/Temp/New");
		//file.encrypt(encryptionAes);
		str.encrypt(encryptionAes);
		//connect can throw Connection refused if there's no server to connect to or sth
		Sender sender(io_service, ip_to_send_to, DEFAULT_PORT);
		sender.connect();
		sender.sendTxtMsg(str, true, key, iv, CFB);
		//sender.sendFile(file, key, iv, true);
	}
	return 0;
}
