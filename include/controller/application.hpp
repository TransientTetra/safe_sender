#ifndef SAFE_SENDER_APPLICATION_HPP
#define SAFE_SENDER_APPLICATION_HPP


#include <string>

class Application
{
private:
	std::string ipAddress;
	std::string otherIP;
protected:
public:
	Application();
	Application(std::string ipAddress);

	void run();
	void connect(std::string ip);
};


#endif //SAFE_SENDER_APPLICATION_HPP
