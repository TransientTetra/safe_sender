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
	RawBytes(std::string str);

	std::string toString();
	void print(std::ostream &o);
};


#endif //SAFE_SENDER_RAW_BYTES_HPP
