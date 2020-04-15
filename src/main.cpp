#include <iostream>
#include <string>
#include "../include/controller/application.hpp"
#include "../include/model/text_message.hpp"
#include "../include/model/encryption_aes.hpp"
#include "../include/model/raw_bytes.hpp"
#include "../include/model/file.hpp"

int main()
{
	EncryptionAES encryptionAes(CBC);
	File file("/home/mkj/Temp/New");
	file.encrypt(encryptionAes);
	file.save("/home/mkj/Temp/New2");
	TextMessage txt("elo");
	txt.print(std::cerr);
	txt.encrypt(encryptionAes);
	txt.print(std::cerr);
	return 0;
}