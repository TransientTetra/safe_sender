#ifndef SAFE_SENDER_SENDABLE_HPP
#define SAFE_SENDER_SENDABLE_HPP


#include "../data_container.hpp"

//an abstract class that all classes that can be sent must inherit from
class Sendable : virtual public DataContainer
{
private:
protected:
public:
	virtual ~Sendable();
};


#endif //SAFE_SENDER_SENDABLE_HPP
