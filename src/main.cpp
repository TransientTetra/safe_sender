#include <iostream>
#include <string>
#include "../include/controller/application.hpp"
#include "../include/model/text_message.hpp"
#include "../include/model/encryption_aes.hpp"
#include "../include/model/raw_bytes.hpp"
#include "../include/model/file.hpp"
#include <crypto++/randpool.h>
#include <crypto++/aes.h>
#include <crypto++/osrng.h>

int main()
{
	EncryptionAES encryptionAes(CFB);
	encryptionAes.setEncryptionKey("6969696969696969");
	encryptionAes.setIV("000");

	File file("/home/mkj/Temp/New");
	file.encrypt(encryptionAes);
	file.save("/home/mkj/Temp/New2");

	TextMessage txt("elo");
	txt.print(std::cout);
	std::cout << " ";
	txt.encrypt(encryptionAes);
	txt.print(std::cout);
	return 0;
}