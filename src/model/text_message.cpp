#include "../../include/model/text_message.hpp"

TextMessage::TextMessage(RawBytes bytes)
: Encryptable(bytes)
{

}

TextMessage::TextMessage(const std::string &str)
: Encryptable(str)
{

}

void TextMessage::print(std::ostream &out)
{
	out << data.toString();
}

void TextMessage::append(std::string str)
{
	data += RawBytes(reinterpret_cast<const unsigned char *>(str.c_str()), str.size());
}

TextMessage::~TextMessage()
{

}

std::string TextMessage::toString()
{
	return data.toString();
}
