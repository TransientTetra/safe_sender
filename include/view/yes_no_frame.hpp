#ifndef SAFE_SENDER_YES_NO_FRAME_HPP
#define SAFE_SENDER_YES_NO_FRAME_HPP


#include "frame.hpp"

class YesNoFrame : public Frame
{
private:
	std::string question;
	bool answer;
protected:
public:
	YesNoFrame(Window *window, const std::string &name);

	void setQuestion(const std::string &question);

	bool getAnswer() const;

	void draw() override;
};


#endif //SAFE_SENDER_YES_NO_FRAME_HPP
