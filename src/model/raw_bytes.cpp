#include "../../include/model/raw_bytes.hpp"
#include <iomanip>

RawBytes::RawBytes(std::string str)
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
