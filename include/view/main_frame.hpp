#ifndef SAFE_SENDER_MAIN_FRAME_HPP
#define SAFE_SENDER_MAIN_FRAME_HPP

#include "frame.hpp"

class MainFrame : public Frame
{
private:
	short currentCipherModeChoice;
	char ipBuf[16];
	char msgBuf[256];
	char keyBuf[256];
protected:
public:
	MainFrame(Window *window, const std::string &name);

	void draw() override;
};


#endif //SAFE_SENDER_MAIN_FRAME_HPP
