#include <iostream>
#include <string>
#include "../include/controller/application.hpp"
#include "../include/model/text_message.hpp"

int main()
{
	TextMessage txt("elo");
	txt.print(std::cerr);
	return 0;
}