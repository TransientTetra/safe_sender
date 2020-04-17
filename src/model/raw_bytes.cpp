#include "../../include/model/raw_bytes.hpp"
#include <iomanip>

RawBytes::RawBytes(const std::string &str)
{
	for (char c : str)
	{
		byteVector.push_back(static_cast<std::byte>(c));
	}
	return;
}

std::string RawBytes::toString()
{
	std::string ret;
	for (std::byte b : byteVector)
	{
		ret.push_back(static_cast<unsigned char>(b));
	}
	return ret;
}

void RawBytes::print(std::ostream &o)
{
	for (std::byte byte : byteVector)
	{
		o << std::setw(2) << std::setfill('0') << std::hex << static_cast<unsigned int>(byte) << " ";
	}
}

void RawBytes::push(const std::byte &byte)
{
	byteVector.push_back(byte);
}

RawBytes::RawBytes()
{

}

const std::byte &RawBytes::getByte(unsigned long i) const
{
	return byteVector[i];
}

std::byte *RawBytes::getVectorPtr()
{
	return &byteVector[0];
}

void RawBytes::pop()
{
	byteVector.pop_back();
}

RawBytes::RawBytes(unsigned long size)
{
	byteVector = std::vector<std::byte>(size);
}

void RawBytes::append(RawBytes other)
{
	for (unsigned long i = 0; i < other.getSize(); ++i)
	{
		push(other.getByte(i));
	}
}

const unsigned long RawBytes::getSize() const
{
	return byteVector.size();
}

void RawBytes::operator=(CryptoPP::SecByteBlock secByteBlock)
{
	*this = RawBytes(secByteBlock);
}

RawBytes::RawBytes(CryptoPP::SecByteBlock secByteBlock)
{
	byteVector = std::vector<std::byte>();
	for (unsigned long i = 0; i < secByteBlock.size(); ++i)
	{
		push(*(reinterpret_cast<std::byte *>(secByteBlock.BytePtr() + i)));
	}
}

CryptoPP::SecByteBlock RawBytes::toSecByteBlock()
{
	return CryptoPP::SecByteBlock(reinterpret_cast<const byte *>(getVectorPtr()), getSize());
}
