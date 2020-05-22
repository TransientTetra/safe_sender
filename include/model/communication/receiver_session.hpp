#ifndef SAFE_SENDER_RECEIVER_SESSION_HPP
#define SAFE_SENDER_RECEIVER_SESSION_HPP


#include "session.hpp"

class ReceiverSession : public Session
{
private:
	void handleIncoming(Packet packet);
	RawBytes receive(unsigned long size);
protected:
public:
	ReceiverSession(tcp::socket&& socket, Application* application);

	void start();
};


#endif //SAFE_SENDER_RECEIVER_SESSION_HPP
