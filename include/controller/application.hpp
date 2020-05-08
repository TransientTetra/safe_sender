#ifndef SAFE_SENDER_APPLICATION_HPP
#define SAFE_SENDER_APPLICATION_HPP


#include <string>
#include <model/communication/receiver.hpp>
#include <model/communication/sender.hpp>
#include <view/window.hpp>
#include <model/encryption/encryption.hpp>

enum ApplicationState
{
	DISCONNECTED,
	CONNECTED,
	ENCRYPTING,
	SENDING
};

class Application
{
private:
	//todo make progressbars work
	ApplicationState state;
	std::string title;
//	std::thread receiverThread;
//	std::thread encryptionThread;
//	std::thread sendingThread;

	std::unique_ptr<Receiver> receiver;
	std::unique_ptr<Sender> sender;
	Window window;

	CipherMode cipherMode;
	std::string filePath;
	std::unique_ptr<File> file;
	std::unique_ptr<TextMessage> textMessage;
	Encryption* encryption;
protected:
public:
	Application(std::string title);

	void run();

	ApplicationState getState();
	void setState(ApplicationState state);

	float getSendingProgress();
	float getEncryptionProgress();
	std::string getIP();
	std::string getChosenFile();

	void setCipherMode(int mode);

	CipherMode getCipherMode() const;

	void connect(std::string ip);
	void disconnect();
	void setFilePath(std::string filePath);

	void encryptAndSendMsg(std::string msg);
	void encryptAndSendFile();

	static bool validateIP(std::string ip);
};


#endif //SAFE_SENDER_APPLICATION_HPP
