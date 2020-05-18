#include "view/frame.hpp"

Frame::Frame(Window *window, std::string name)
: window(window)
{
	this->name = name;
	display = false;
}

void Frame::draw()
{
}

void Frame::attachApplication(Application *application)
{
	this->application = application;
}


bool Frame::isDisplay() const
{
	return display;
}

void Frame::setDisplay(bool display)
{
	this->display = display;
}