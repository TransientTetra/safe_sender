#ifndef SAFE_SENDER_ENCRYPTION_HPP
#define SAFE_SENDER_ENCRYPTION_HPP
#include <string>
#include "raw_bytes.hpp"

//a virtual class that all encryption algorithms must inherit from
class Encryption
{
private:
protected:
public:
	virtual RawBytes encrypt(const RawBytes &data) = 0;
};


#endif //SAFE_SENDER_ENCRYPTION_HPP
