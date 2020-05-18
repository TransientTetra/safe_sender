#ifndef SAFE_SENDER_INFO_FRAME_HPP
#define SAFE_SENDER_INFO_FRAME_HPP


#include "frame.hpp"

class InfoFrame : public Frame
{
private:
	std::string text;
protected:
public:
	InfoFrame(Window *window, const std::string &name);

	void setText(const std::string &text);

	void draw() override;
};


#endif //SAFE_SENDER_INFO_FRAME_HPP
