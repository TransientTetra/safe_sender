#ifndef SAFE_SENDER_TEXT_MESSAGE_HPP
#define SAFE_SENDER_TEXT_MESSAGE_HPP
#include "sendable.hpp"
#include "encryptable.hpp"
#include "raw_bytes.hpp"
#include <string>
#include <ostream>

class TextMessage : public Sendable, public Encryptable
{
private:
protected:
public:
	TextMessage(std::string text);
	void encrypt(Encryption &encryption);
	void print(std::ostream &out);
	void append(std::string str);
};


#endif //SAFE_SENDER_TEXT_MESSAGE_HPP
