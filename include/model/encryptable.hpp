//
// Created by mkj on 3/7/20.
//

#ifndef SAFE_SENDER_ENCRYPTABLE_HPP
#define SAFE_SENDER_ENCRYPTABLE_HPP
#include "encryption.hpp"

//an abstract class that all objects that can be encrypted need to inherit from
class Encryptable
{
private:
protected:
public:
	virtual void encrypt(Encryption &encryption) = 0;
};


#endif //SAFE_SENDER_ENCRYPTABLE_HPP
