#include <iostream>
#include <string>
#include "../include/controller/application.hpp"
#include "../include/model/text_message.hpp"
#include "../include/model/encryption_aes.hpp"
#include "../include/model/raw_bytes.hpp"
#include "../include/model/file.hpp"

int main()
{
	RawBytes a("elo");
	RawBytes b("lol");
	a.append(b);
	std::cout << a.toString();
	EncryptionAES encryptionAes(CFB);
	File file("/home/mkj/Temp/vpn.zip");
	file.encrypt(encryptionAes);
	file.save("/home/mkj/Temp/New2");
	TextMessage txt("elo");
	txt.print(std::cout);
	txt.encrypt(encryptionAes);
	txt.print(std::cout);
	return 0;
}