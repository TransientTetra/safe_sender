#ifndef SAFE_SENDER_ENCRYPTABLE_HPP
#define SAFE_SENDER_ENCRYPTABLE_HPP

#include "../data_container.hpp"

class Encryption;

//an abstract class that all objects that can be encrypted need to inherit from
class Encryptable : virtual public DataContainer
{
private:
protected:
	bool encrypted;
public:
	Encryptable();
	Encryptable(const std::string& str);
	Encryptable(RawBytes &bytes);

	virtual void encrypt(Encryption &encryption);
	virtual void decrypt(Encryption &encryption);
	virtual bool isEncrypted();
};


#endif //SAFE_SENDER_ENCRYPTABLE_HPP
