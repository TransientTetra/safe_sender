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

	frame.reset(new MainFrame(&window, "Main frame"));
	infoFrame.reset(new InfoFrame(&window, "Info"));
	yesNoFrame.reset(new YesNoFrame(&window, "Query"));
	frame->attachApplication(this);
	infoFrame->attachApplication(this);
	yesNoFrame->attachApplication(this);

	while (window.isOpen())
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if ((event.type == SDL_QUIT) || (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE
				&& event.window.windowID == SDL_GetWindowID(window.getSDLWindow())))
			{
				//todo when sender is connected to receiver and receiver tries to exit program it hangs
				//until sender quits
				window.setClose();
			}
		}
		frame->draw();
		infoFrame->draw();
		yesNoFrame->draw();
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
		sender->disconnect();
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
	if (getState() == DISCONNECTED)
	{
		displayError("Error: Application not connected");
		return;
	}
	if (getState() == CONNECTED)
	{
		if (msg == "")
		{
			displayError("Error: Message is empty");
			return;
		}
		textMessage.reset(new TextMessage(msg));
		EncryptionKey ekey(key);
		if (key != "")
		{
			encryption.reset(new EncryptionAES(getCipherMode()));
			textMessage->encrypt(*encryption);
		}
		sendingThread = std::thread(&Sender::sendTxtMsg, sender.get(), std::ref(*textMessage),
			std::ref(ekey), std::ref(iv), getCipherMode());
	}
}

void Application::encryptAndSendFile(std::string key)
{
	if (getState() == DISCONNECTED)
	{
		displayError("Error: Application not connected");
		return;
	}
	if (getState() == CONNECTED)
	{
		if (filePath == "")
		{
			displayError("Error: No file selected");
			return;
		}
		file.reset(new File(filePath));
		EncryptionKey ekey(key);
		if (key != "")
		{
			encryption.reset(new EncryptionAES(getCipherMode()));
			textMessage->encrypt(*encryption);
		}
		sendingThread = std::thread(&Sender::sendFile, sender.get(), std::ref(*file),
					    std::ref(ekey), std::ref(iv), getCipherMode());
	}
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

bool Application::askYesNo(std::string m)
{
	yesNoFrame->setQuestion(m);
	yesNoFrame->setDisplay(true);
	while (yesNoFrame->isDisplay());
	return yesNoFrame->getAnswer();
}

const std::string &Application::askPath()
{
	frame->openDirBrowser();
	while(frame->isDirBrowserOpen());
	return frame->getDirPath();
}
