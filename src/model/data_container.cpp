#include "../../include/model/data_container.hpp"

RawBytes &DataContainer::getData()
{
	return data;
}

unsigned long DataContainer::getDataSize() const
{
	return data.size();
}
