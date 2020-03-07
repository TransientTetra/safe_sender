//
// Created by mkj on 3/7/20.
//

#ifndef SAFE_SENDER_TEXT_MESSAGE_HPP
#define SAFE_SENDER_TEXT_MESSAGE_HPP
#include "sendable.hpp"
#include "encryptable.hpp"
#include <string>
#include <ostream>

class TextMessage : public Sendable, public Encryptable
{
private:
	std::string rawText;
protected:
public:
	TextMessage();
	TextMessage(std::string text);
	void encrypt(Encryption &encryption);
	void print(std::ostream &out);
};


#endif //SAFE_SENDER_TEXT_MESSAGE_HPP
