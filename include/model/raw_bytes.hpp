#ifndef SAFE_SENDER_RAW_BYTES_HPP
#define SAFE_SENDER_RAW_BYTES_HPP

#include <vector>
#include <cstddef>
#include <string>
#include <ostream>
#include <crypto++/secblock.h>

class RawBytes
{
private:
	std::vector<std::byte> byteVector;
protected:
public:
	RawBytes();
	RawBytes(std::string str);
	RawBytes(unsigned long size);
	RawBytes(CryptoPP::SecByteBlock secByteBlock);

	std::string toString();
	void print(std::ostream &o);
	void push(const std::byte &byte);
	void pop();

	unsigned long getSize();
	const std::byte &getByte(unsigned long i) const;
	std::byte *getVectorPtr();

	void operator=(CryptoPP::SecByteBlock secByteBlock);

	void append(RawBytes other);
};


#endif //SAFE_SENDER_RAW_BYTES_HPP
