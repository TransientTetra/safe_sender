#ifndef SAFE_SENDER_RAW_BYTES_HPP
#define SAFE_SENDER_RAW_BYTES_HPP

#include <vector>
#include <cstddef>
#include <string>
#include <ostream>

class RawBytes
{
private:
	std::vector<std::byte> byteVector;
protected:
public:
	RawBytes();
	RawBytes(std::string str);
	RawBytes(unsigned long size);

	std::string toString();
	void print(std::ostream &o);
	void push(const std::byte &byte);
	void pop();
	unsigned long getSize();
	const std::byte &getByte(unsigned long i) const;
	std::byte *getVectorPtr();

	void append(RawBytes other);
};


#endif //SAFE_SENDER_RAW_BYTES_HPP
