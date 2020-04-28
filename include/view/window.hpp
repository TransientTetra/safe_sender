#ifndef SAFE_SENDER_WINDOW_HPP
#define SAFE_SENDER_WINDOW_HPP

#include "imgui/imgui.h"
#include "imgui/examples/imgui_impl_sdl.h"
#include "imgui/examples/imgui_impl_opengl3.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>

class Window
{
private:
protected:
	bool open;
	ImVec4 bgColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	SDL_Window* sdlWindow;
	SDL_GLContext glContext;
	ImGuiIO* io;
	std::string title;
	int posX;
	int posY;
	int height;
	int width;
public:
	Window(std::string title, int posX, int posY, int height, int width);
	~Window();

	void render();
	bool isOpen();
	void setClose();
	SDL_Window* getSDLWindow();
};


#endif //SAFE_SENDER_WINDOW_HPP
