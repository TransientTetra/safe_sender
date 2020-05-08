#include <filesystem>
#include "view/main_frame.hpp"
#include "controller/application.hpp"
#include "constants.hpp"

Application::Application(std::string title)
: window(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_WIDTH)
{
	this->title = title;
	state = DISCONNECTED;
}

void Application::run()
{
	receiver.reset(new Receiver(ioService, DEFAULT_PORT));
	receiver->attachApplication(this);
	//todo receiver thread
	receiverThread = receiver->getListenerThread();
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
	if (getState() == SENDING)
		return sender->getProgress();
	return 0;
}

float Application::getEncryptionProgress()
{
	if (getState() == ENCRYPTING)
		return encryption->getProgress();
	return 0;
}

void Application::setCipherMode(int mode)
{
	cipherMode = static_cast<CipherMode>(mode);
}

void Application::connect(std::string ip)
{
	if (!validateIP(ip))
		//todo show error message
		return;
	sender.reset(new Sender(ioService, ip, DEFAULT_PORT));
	if (sender->connect())
		setState(CONNECTED);
	else
	{
		//todo show error message
		disconnect();
	}
}

void Application::disconnect()
{
	if (getState() == CONNECTED)
	{
//		delete sender;
		setState(DISCONNECTED);
	}
}

void Application::setFilePath(std::string filePath)
{
	if (!std::filesystem::exists(filePath))
	{
		return;
	}
	this->filePath = filePath;
}

void Application::encryptAndSendMsg(std::string msg)
{
	if (msg == "")
	{
		//todo display error saying msg is empty
		return;
	}
	if (getState() == CONNECTED)
	{
		textMessage.reset(new TextMessage(msg));
	}
}

void Application::encryptAndSendFile()
{

}

std::string Application::getIP()
{
	if (getState() == CONNECTED)
		return sender->getReceiverIP();
	else
		return "";
}

std::string Application::getChosenFile()
{
	return filePath;
}

ApplicationState Application::getState()
{
	return state;
}

void Application::setState(ApplicationState state)
{
	this->state = state;
}

bool Application::validateIP(std::string ip)
{
	asio::error_code ec;
	address::from_string(ip, ec);
	if (ec)
		return false;
	return true;
}

CipherMode Application::getCipherMode() const
{
	return cipherMode;
}
