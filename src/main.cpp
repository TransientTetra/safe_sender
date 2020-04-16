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
	CryptoPP::AutoSeededRandomPool rnd;
	CryptoPP::SecByteBlock key(0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
	rnd.GenerateBlock( key, key.size() );
	RawBytes a("elo");
	a = key;
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