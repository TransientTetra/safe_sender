#ifndef SAFE_SENDER_SENDABLE_HPP
#define SAFE_SENDER_SENDABLE_HPP

//an abstract class that all classes that can be sent must inherit from
class Sendable
{
private:
protected:
	unsigned long long int dataLengthBytes; //number of bytes of the object to be sent
public:
	unsigned long long int getDataLength();
};


#endif //SAFE_SENDER_SENDABLE_HPP
