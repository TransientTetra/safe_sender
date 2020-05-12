#ifndef SAFE_SENDER_DATA_CONTAINER_HPP
#define SAFE_SENDER_DATA_CONTAINER_HPP


#include "raw_bytes.hpp"

class DataContainer
{
private:
protected:
	RawBytes data;
public:
	virtual ~DataContainer();
	virtual RawBytes &getData();
	virtual unsigned long getDataSize() const;
};


#endif //SAFE_SENDER_DATA_CONTAINER_HPP
