#ifndef SAFE_SENDER_MAIN_FRAME_HPP
#define SAFE_SENDER_MAIN_FRAME_HPP

#include <controller/application.hpp>
#include "frame.hpp"

class MainFrame : public Frame
{
private:
	ModifiableFields* applicationFields;
protected:
public:
	MainFrame(Window *window, const std::string &name, ModifiableFields* modifiableFields);

	void draw(Receiver *receiver, Sender *sender);
};


#endif //SAFE_SENDER_MAIN_FRAME_HPP
