#include "yes_no_frame.hpp"

YesNoFrame::YesNoFrame(Window *window, const std::string &name)
: Frame(window, name)
{
	answer = false;
}

void YesNoFrame::draw()
{
	if (!display) return;

	Frame::draw();

	ImGui::Begin(name.c_str());

	ImGui::SetWindowSize(ImVec2(300, 100));
	ImGui::Text(question.c_str());
	if (ImGui::Button("Yes"))
	{
		answer = true;
		display = false;
	}
	ImGui::SameLine(ImGui::GetWindowWidth()-30);
	if (ImGui::Button("No"))
	{
		answer = false;
		display = false;
	}

	ImGui::End();
	ImGui::EndFrame();
}

void YesNoFrame::setQuestion(const std::string &question)
{
	YesNoFrame::question = question;
}

bool YesNoFrame::getAnswer() const
{
	return answer;
}
