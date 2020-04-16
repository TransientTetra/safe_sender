#ifndef SAFE_SENDER_ENCRYPTION_HPP
#define SAFE_SENDER_ENCRYPTION_HPP
#include <string>
#include "raw_bytes.hpp"

enum CipherMode
{
	ECB,
	CBC,
	CFB,
	OFB
};
//a virtual class that all encryption algorithms must inherit from
class Encryption
{
private:
protected:
public:
	virtual void encrypt(RawBytes &data) = 0;
	virtual void decrypt(RawBytes &data) = 0;
};


#endif //SAFE_SENDER_ENCRYPTION_HPP
