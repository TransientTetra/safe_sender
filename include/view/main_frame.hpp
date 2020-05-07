#ifndef SAFE_SENDER_MAIN_FRAME_HPP
#define SAFE_SENDER_MAIN_FRAME_HPP

#include "frame.hpp"
#include <imgui-filebrowser/imfilebrowser.h>


class MainFrame : public Frame
{
private:
	short currentCipherModeChoice;
	char ipBuf[16];
	char msgBuf[256];
	char keyBuf[256];
	ImGui::FileBrowser fileBrowser;
protected:
public:
	MainFrame(Window *window, const std::string &name);

	void draw() override;
};


#endif //SAFE_SENDER_MAIN_FRAME_HPP
