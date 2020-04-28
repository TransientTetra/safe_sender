#ifndef SAFE_SENDER_FRAME_HPP
#define SAFE_SENDER_FRAME_HPP


#include "window.hpp"

class Frame
{
private:
protected:
	Window* window;
	std::string name;
public:
	Frame(Window* window, std::string name);
	virtual void draw();
};


#endif //SAFE_SENDER_FRAME_HPP
