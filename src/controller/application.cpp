#include "boost/asio.hpp"
#include <iostream>
#include "view/main_frame.hpp"
#include "controller/application.hpp"
#include "constants.hpp"

Application::Application(std::string title)
: window(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_WIDTH)
{
	this->title = title;
	modifiableFields.ipToSendTo = "None";
	modifiableFields.encryptionProgress = 0;
	modifiableFields.sendingProgress = 0;
	modifiableFields.message = "";
	modifiableFields.filePath = "";
	modifiableFields.key = "";
	modifiableFields.cipherMode = CFB;
}

void Application::run()
{
	receiver = new Receiver(DEFAULT_PORT);
	receiverThread = std::thread(&Receiver::listenAndReceive, receiver);
	MainFrame frame(&window, "Main frame", &modifiableFields);
	while (window.isOpen())
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if ((event.type == SDL_QUIT) || (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE
				&& event.window.windowID == SDL_GetWindowID(window.getSDLWindow())))
			{
				window.setClose();
				//todo exit in humane way (end receiver thread)
				std::terminate();
			}
		}
		frame.draw(receiver, sender);
		window.render();
	}
}
