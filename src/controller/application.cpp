#include <filesystem>
#include <model/encryption/encryption_aes.hpp>
#include "view/main_frame.hpp"
#include "controller/application.hpp"
#include "constants.hpp"

Application::Application(std::string title)
: window(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_WIDTH),
iv("0")
{
	this->title = title;
	state = DISCONNECTED;
}

Application::~Application()
{
	ioService.stop();
	if (receiverThread.joinable()) receiverThread.join();
	if (sendingThread.joinable()) sendingThread.join();
	if (encryptionThread.joinable()) encryptionThread.join();
}

void Application::run()
{
	receiver.reset(new Receiver(ioService, DEFAULT_PORT, this));
	receiver->listen();
	receiverThread = std::thread([&]{ioService.run();});
	MainFrame frame(&window, "Main frame");
	infoFrame.reset(new InfoFrame(&window, "Info"));
	frame.attachApplication(this);
	infoFrame->attachApplication(this);

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
			}
		}
		frame.draw();
		infoFrame->draw();
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
	{
		displayError("Error: Invalid IP address");
		return;
	}
	sender.reset(new Sender(ioService, ip, DEFAULT_PORT, this));
	if (sender->connect())
		setState(CONNECTED);
	else
	{
		displayError("Error: Could not connect");
		disconnect();
	}
}

void Application::disconnect()
{
	if (getState() == CONNECTED)
	{
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

void Application::encryptAndSendMsg(std::string msg, std::string key)
{
	if (msg == "")
	{
		displayError("Error: Message is empty");
		return;
	}
	if (getState() == CONNECTED)
	{
		textMessage.reset(new TextMessage(msg));
		EncryptionKey ekey(key);
		if (key != "")
		{
			encryption.reset(new EncryptionAES(getCipherMode()));
			textMessage->encrypt(*encryption);
		}
		sender->sendTxtMsg(*textMessage, ekey, iv, getCipherMode());
	}
}

void Application::encryptAndSendFile(std::string key)
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

void Application::displayError(std::string e)
{
	infoFrame->setText(e);
	infoFrame->setDisplay(true);
}
