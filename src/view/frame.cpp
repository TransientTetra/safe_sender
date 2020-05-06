#include "view/frame.hpp"

Frame::Frame(Window *window, std::string name)
: window(window), name(name)
{

}

void Frame::draw()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(window->getSDLWindow());
	ImGui::NewFrame();
}

void Frame::attachApplication(Application *application)
{
	this->application = application;
}
