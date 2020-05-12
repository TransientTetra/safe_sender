#ifndef SAFE_SENDER_INITIALIZATION_VECTOR_HPP
#define SAFE_SENDER_INITIALIZATION_VECTOR_HPP


#include "communication/sendable.hpp"
#include "encryption/encryptable.hpp"

class InitializationVector : public Encryptable, public Sendable
{
private:
protected:
public:
	InitializationVector();
	InitializationVector(const std::string &str);
	InitializationVector(RawBytes bytes);
	~InitializationVector();
};


#endif //SAFE_SENDER_INITIALIZATION_VECTOR_HPP
