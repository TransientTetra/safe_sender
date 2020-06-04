#ifndef SAFE_SENDER_TEXT_INPUT_FRAME_HPP
#define SAFE_SENDER_TEXT_INPUT_FRAME_HPP


#include "frame.hpp"

class TextInputFrame : public Frame
{
private:
	char buf[32];
	std::string message;
protected:
public:
	TextInputFrame(Window *window, const std::string &name);

	void setMessage(const std::string &message);

	void draw() override;
};


#endif //SAFE_SENDER_TEXT_INPUT_FRAME_HPP
