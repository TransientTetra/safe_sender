#ifndef SAFE_SENDER_ENCRYPTABLE_HPP
#define SAFE_SENDER_ENCRYPTABLE_HPP

#include "raw_bytes.hpp"

class Encryption;

//an abstract class that all objects that can be encrypted need to inherit from
class Encryptable
{
private:
protected:
	RawBytes data;
	bool isEncrypted;
public:
	Encryptable();
	Encryptable(const std::string& str);
	Encryptable(RawBytes &bytes);

	virtual unsigned long getDataSize() const;

	virtual void encrypt(Encryption &encryption);
	virtual void decrypt(Encryption &encryption);

	virtual RawBytes &getData();
};


#endif //SAFE_SENDER_ENCRYPTABLE_HPP
