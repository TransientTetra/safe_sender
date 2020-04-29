#ifndef SAFE_SENDER_MAIN_FRAME_HPP
#define SAFE_SENDER_MAIN_FRAME_HPP


#include "frame.hpp"

class MainFrame : public Frame
{
private:
	std::string* applicationIPToSendTo;
	float* applicationEncryptionProgress;
	float* applicationSendingProgress;
protected:
public:
	MainFrame(Window *window, const std::string &name, std::string* ip, float* encryptionProg, float* sendingProg);

	void draw() override;
};


#endif //SAFE_SENDER_MAIN_FRAME_HPP
