#include "view/info_frame.hpp"
#include "controller/application.hpp"

InfoFrame::InfoFrame(Window *window, const std::string &name)
: Frame(window, name)
{
	display = false;
}

void InfoFrame::setText(const std::string &text)
{
	InfoFrame::text = text;
}

void InfoFrame::draw()
{
	if (!display) return;

	Frame::draw();

	ImGui::Begin(name.c_str());

	ImGui::Text(text.c_str());
	ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Close").x) * 0.5f);
	if (ImGui::Button("Close")) display = false;

	ImGui::End();
	ImGui::EndFrame();
}
