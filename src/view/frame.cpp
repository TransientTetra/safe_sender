#include "view/frame.hpp"

Frame::Frame(Window *window, std::string name)
: window(window), name(name)
{

}

void Frame::draw()
{
}

void Frame::attachApplication(Application *application)
{
	this->application = application;
}
