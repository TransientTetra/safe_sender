#include <filesystem>
#include <model/encryption/encryption_aes.hpp>
#include <model/encryption/encryption_sha_256.hpp>
#include <cryptopp/osrng.h>
#include <iostream>
#include "view/main_frame.hpp"
#include "controller/application.hpp"
#include "constants.hpp"

Application::Application(std::string title)
: window(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_WIDTH)
{
	this->title = title;
	state = WAITING_FOR_LOGIN;
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
	frame.reset(new MainFrame(&window, "Main frame"));
	infoFrame.reset(new InfoFrame(&window, "Info"));
	yesNoFrame.reset(new YesNoFrame(&window, "Query"));
	textInputFrame.reset(new TextInputFrame(&window, "Input password"));
	textInputFrame->attachApplication(this);
	frame->attachApplication(this);
	infoFrame->attachApplication(this);
	yesNoFrame->attachApplication(this);

	textInputFrame->setDisplay(true);
	textInputFrame->setMessage("Please put your password in");

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
		textInputFrame->draw();
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
	if (getState() == DISCONNECTED)
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
	if (!getState() == WAITING_FOR_LOGIN) return;
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
	if (not loginCorrect) return;
	if (getState() == CONNECTED)
	{
		if (msg == "")
		{
			displayError("Error: Message is empty");
			return;
		}
		textMessage.reset(new TextMessage(msg));
		CryptoPP::AutoSeededRandomPool rng;
		RawBytes key(0x00, DEFAULT_SESSION_KEY_SIZE);
		RawBytes iv(0x00, DEFAULT_IV_SIZE);
		rng.GenerateBlock(key, key.size());
		rng.GenerateBlock(iv, iv.size());
		EncryptionKey sessionKey(key);
		EncryptionSHA256 sha;
		sessionKey.encrypt(sha);
		encryption.reset(new EncryptionAES(getCipherMode()));
		encryption->setEncryptionKey(sessionKey);
		encryption->setIV(iv.toString().c_str());
		textMessage->encrypt(*encryption);
		sender->handleSend(textMessage.get(), *encryption, TXT_MSG);
	}
}

void Application::encryptAndSendFile(std::string key)
{
	if (getState() == DISCONNECTED)
	{
		displayError("Error: Application not connected");
		return;
	}
	if (not loginCorrect) return;
	if (getState() == CONNECTED)
	{
		if (filePath == "")
		{
			displayError("Error: No file selected");
			return;
		}
		file.reset(new File(filePath));
		CryptoPP::AutoSeededRandomPool rng;
		RawBytes key(0x00, DEFAULT_SESSION_KEY_SIZE);
		rng.GenerateBlock(key, key.size());
		EncryptionKey sessionKey(key);
		EncryptionSHA256 sha;
		sessionKey.encrypt(sha);
		encryption.reset(new EncryptionAES(getCipherMode()));
		encryption->setEncryptionKey(sessionKey);
		encryption->setIV(DEFAULT_IV);
		file->encrypt(*encryption);
		sender->handleSend(file.get(), *encryption, FILE_MSG);
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
	auto ip_addr = address::from_string(ip, ec);
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
	if (!getState() == WAITING_FOR_LOGIN) return;
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
	if (!getState() == WAITING_FOR_LOGIN) return "";
	frame->openDirBrowser();
	while(frame->isDirBrowserOpen());
	return frame->getDirPath();
}

void Application::login(std::string password)
{
	setState(DISCONNECTED);
	std::string currPath = std::filesystem::current_path();
	std::filesystem::create_directory(currPath + "/keys/");
	std::filesystem::create_directory(currPath + "/keys/private/");
	std::filesystem::create_directory(currPath + "/keys/public/");
	std::string privPath = currPath + "/keys/private/private.dat";
	std::string publPath = currPath + "/keys/public/public.dat";

	EncryptionKey userKey(password);
	EncryptionSHA256 sha;
	userKey.encrypt(sha);
	if (!std::filesystem::exists(privPath) or !std::filesystem::exists(publPath))
	{
		displayError("First login, creating new RSA keys");
		encryptionRSA.generateKeyPair();
		encryptionRSA.encryptKeysToFile(privPath, publPath, userKey);
		loginCorrect = true;
	}
	else
	{
		loginCorrect = encryptionRSA.decryptKeysFromFile(privPath, publPath, userKey);
	}
	receiver.reset(new Receiver(ioService, DEFAULT_PORT, this));
	receiver->listen();
	receiverThread = std::thread([&]{ioService.run();});
}

CryptoPP::RSA::PublicKey& Application::getPublicKey()
{
	return encryptionRSA.getPublicKey();
}

EncryptionRSA &Application::getEncryption()
{
	return encryptionRSA;
}

bool Application::isLoginCorrect() const
{
	return loginCorrect;
}
