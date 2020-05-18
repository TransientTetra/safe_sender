#ifndef SAFE_SENDER_FRAME_HPP
#define SAFE_SENDER_FRAME_HPP

#include "window.hpp"
class Application;

class Frame
{
private:
protected:
	Application* application;
	Window* window;
	std::string name;
public:
	Frame(Window* window, std::string name);
	virtual void draw();
	virtual void attachApplication(Application *application);
};


#endif //SAFE_SENDER_FRAME_HPP
