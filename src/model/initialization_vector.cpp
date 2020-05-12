#include "../../include/model/initialization_vector.hpp"

InitializationVector::InitializationVector(const std::string &str)
: Encryptable(str)
{

}

InitializationVector::InitializationVector(RawBytes bytes)
: Encryptable(bytes)
{

}

InitializationVector::InitializationVector()
{

}

InitializationVector::~InitializationVector()
{

}
