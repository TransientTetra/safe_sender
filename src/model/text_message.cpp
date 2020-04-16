#include "../../include/model/text_message.hpp"

void TextMessage::encrypt(Encryption &encryption)
{
	isEncrypted = true;
	encryption.encrypt(data);
}

TextMessage::TextMessage(std::string text)
{
	isEncrypted = false;
	data = RawBytes(text);
}

void TextMessage::print(std::ostream &out)
{
	out << data.toString();
}

void TextMessage::append(std::string str)
{
	data.append(RawBytes(str));
}
