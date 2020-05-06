#include "boost/asio.hpp"
#include <iostream>
#include "view/main_frame.hpp"
#include "controller/application.hpp"
#include "constants.hpp"

Application::Application(std::string title)
: window(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_WIDTH)
{
	this->title = title;
}

void Application::run()
{
	boost::asio::io_service ioService;
	receiver = new Receiver(ioService, DEFAULT_PORT);
	receiverThread = std::thread(&Receiver::listenAndReceive, receiver);
	MainFrame frame(&window, "Main frame");
	frame.attachApplication(this);
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
		frame.draw();
		window.render();
	}
}

float Application::getSendingProgress()
{
	return 0;
}

float Application::getEncryptionProgress()
{
	return 0;
}

void Application::setCipherMode(int mode)
{

}

void Application::connect(std::string ip)
{

}

void Application::chooseFile()
{
	//todo file browsing
}

void Application::disconnect()
{

}

void Application::encryptAndSendMsg()
{

}

void Application::encryptAndSendFile()
{

}

std::string Application::getIP()
{
	return std::string();
}

std::string Application::getChosenFile()
{
	return std::string();
}
