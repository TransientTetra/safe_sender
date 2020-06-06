#include "view/text_input_frame.hpp"
#include "controller/application.hpp"

TextInputFrame::TextInputFrame(Window *window, const std::string &name)
: Frame(window, name)
{
	buf[0] = '\0';
}

void TextInputFrame::setMessage(const std::string &message)
{
	TextInputFrame::message = message;
}

void TextInputFrame::draw()
{
	if (!display) return;
	Frame::draw();
	ImGui::Begin(name.c_str());

	ImGui::SetWindowSize(ImVec2(350, 100));
	ImGui::Text(message.c_str());
	ImGui::InputText("##buf", buf, sizeof(buf) / sizeof(char));

	if (ImGui::Button("Ok"))
	{
		if (std::string(buf) != "")
		{
			display = false;
			application->login(std::string(buf));
		}
	}

	ImGui::End();
	ImGui::EndFrame();
}
