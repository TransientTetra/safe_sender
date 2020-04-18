#ifndef SAFE_SENDER_RAW_BYTES_HPP
#define SAFE_SENDER_RAW_BYTES_HPP

#include <vector>
#include <cstddef>
#include <string>
#include <ostream>
#include <crypto++/secblock.h>

class RawBytes : public CryptoPP::SecByteBlock
{
private:
protected:
public:
	RawBytes();
	RawBytes(const std::string &str);
	RawBytes(unsigned long size);

	std::string toString();
	void print(std::ostream &o);

	const byte &getByte(unsigned long i) const;
};


#endif //SAFE_SENDER_RAW_BYTES_HPP
