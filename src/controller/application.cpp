#include "boost/asio.hpp"
#include <iostream>
#include "../../include/controller/application.hpp"

Application::Application()
{
}

Application::Application(std::string ipAddress)
: ipAddress(ipAddress)
{

}

void Application::connect(std::string ip)
{
	otherIP = ip;
}

void print(const boost::system::error_code &e)
{
	std::cout << "end";
}
void Application::run()
{
}
