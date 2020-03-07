#include "../../include/model/text_message.hpp"

void TextMessage::encrypt(Encryption &encryption)
{
	RawBytes preEncryption = txtToRawBytes();
	RawBytes postEncryption = encryption.encrypt(preEncryption);
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
