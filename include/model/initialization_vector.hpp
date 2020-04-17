#ifndef SAFE_SENDER_INITIALIZATION_VECTOR_HPP
#define SAFE_SENDER_INITIALIZATION_VECTOR_HPP


#include "sendable.hpp"
#include "encryptable.hpp"

class InitializationVector : public Encryptable, public Sendable
{
private:
protected:
public:
	InitializationVector();
	InitializationVector(const std::string &str);
	InitializationVector(RawBytes bytes);
};


#endif //SAFE_SENDER_INITIALIZATION_VECTOR_HPP