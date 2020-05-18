#ifndef SAFE_SENDER_INFO_FRAME_HPP
#define SAFE_SENDER_INFO_FRAME_HPP


#include "frame.hpp"

class InfoFrame : public Frame
{
private:
	std::string text;
	bool display;
protected:
public:
	InfoFrame(Window *window, const std::string &name);

	void setText(const std::string &text);

	void draw() override;

	bool isDisplay() const;
	void setDisplay(bool display);
};


#endif //SAFE_SENDER_INFO_FRAME_HPP
