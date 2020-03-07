#include "../../include/model/text_message.hpp"

void TextMessage::encrypt(Encryption &encryption)
{
	RawBytes preEncryption(rawText);
	RawBytes postEncryption = encryption.encrypt(preEncryption);
	rawText = postEncryption.toString();
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

void TextMessage::append(std::string str)
{
	rawText.append(str);
	return;
}
