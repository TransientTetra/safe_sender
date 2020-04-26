#ifndef SAFE_SENDER_RAW_BYTES_HPP
#define SAFE_SENDER_RAW_BYTES_HPP

#include <string>
#include <ostream>
#include "cryptopp/secblock.h"

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

	const CryptoPP::byte &getByte(unsigned long i) const;
};


#endif //SAFE_SENDER_RAW_BYTES_HPP
