#ifndef SAFE_SENDER_APPLICATION_HPP
#define SAFE_SENDER_APPLICATION_HPP


#include <string>
#include <model/communication/receiver.hpp>
#include <model/communication/sender.hpp>
#include <view/window.hpp>
#include <model/encryption/encryption.hpp>
#include <view/main_frame.hpp>
#include <view/yes_no_frame.hpp>
#include <view/info_frame.hpp>
#include <view/text_input_frame.hpp>
#include <model/encryption/encryption_rsa.hpp>

enum ApplicationState
{
	DISCONNECTED,
	CONNECTED,
	ENCRYPTING,
	SENDING,
	WAITING_FOR_LOGIN
};

class Application
{
private:
	//todo make progressbars work
	ApplicationState state;
	std::string title;
	std::thread receiverThread;
	std::thread encryptionThread;
	std::thread sendingThread;

	std::unique_ptr<Receiver> receiver;
	std::unique_ptr<Sender> sender;
	Window window;
	asio::io_service ioService;

	std::unique_ptr<MainFrame> frame;
	std::unique_ptr<InfoFrame> infoFrame;
	std::unique_ptr<YesNoFrame> yesNoFrame;
	std::unique_ptr<TextInputFrame> textInputFrame;

	CipherMode cipherMode;
	std::string filePath;
	std::unique_ptr<File> file;
	std::unique_ptr<TextMessage> textMessage;
	std::unique_ptr<Encryption> encryption;

	bool loginCorrect;

	EncryptionRSA encryptionRSA;
protected:
public:
	Application(std::string title);
	~Application();

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

	void encryptAndSendMsg(std::string msg, std::string key);
	void encryptAndSendFile(std::string key);

	void displayError(std::string e);
	bool askYesNo(std::string m);

	static bool validateIP(std::string ip);

	const std::string &askPath();

	void login(std::string password);
	CryptoPP::RSA::PublicKey& getPublicKey();
};


#endif //SAFE_SENDER_APPLICATION_HPP
