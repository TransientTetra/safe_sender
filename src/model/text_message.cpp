//
// Created by mkj on 3/7/20.
//

#include "../../include/model/text_message.hpp"

void TextMessage::encrypt(Encryption &encryption)
{
	encryption.encrypt()
	return;
}

TextMessage::TextMessage()
{
	rawText = "";
	return;
}

TextMessage::TextMessage(std::string text)
{
	rawText = text;
	return;
}

void TextMessage::print(std::ostream &out)
{
	out << rawText;
	return;
}
