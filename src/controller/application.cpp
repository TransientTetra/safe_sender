#include "boost/asio.hpp"
#include <iostream>
#include "view/main_frame.hpp"
#include "controller/application.hpp"
#include "constants.hpp"

Application::Application(std::string title)
: window(title, SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_WIDTH)
{
	ip = "None";
	this->title = title;
	encryptionProgress = 0;
	sendingProgress = 0;
}

void Application::run()
{
	boost::asio::io_service ioService;
	receiver = new Receiver(ioService, DEFAULT_PORT);
	MainFrame frame(&window, "Main frame", &ip, &encryptionProgress, &sendingProgress);
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
}
