#include "../include/view/main_frame.hpp"

// Main code
int main(int, char**)
{
	Window window("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 900);
	MainFrame frame(&window, "frame");
	while (window.isOpen())
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT)
				window.setClose();
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE
			&& event.window.windowID == SDL_GetWindowID(window.getSDLWindow()))
				window.setClose();
		}
		frame.draw();
		window.render();
	}

	return 0;
}
