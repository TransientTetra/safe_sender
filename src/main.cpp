#include <iostream>
#include <string>
#include "../include/controller/application.hpp"
#include "../include/model/text_message.hpp"
#include "../include/model/encryption_aes.hpp"
#include "../include/model/raw_bytes.hpp"

int main()
{
	EncryptionAES encryptionAes;
	TextMessage txt("elo");
	txt.print(std::cerr);
	txt.encrypt(encryptionAes);
	txt.print(std::cerr);
	return 0;
}