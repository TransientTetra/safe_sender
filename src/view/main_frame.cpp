#include "view/main_frame.hpp"

MainFrame::MainFrame(Window *window, const std::string &name)
: Frame(window, name)
{}

void MainFrame::draw()
{
	Frame::draw();
	static float f = 0.0f;
	static int counter = 0;
	static bool b = true;

	ImGui::Begin("Hello, world!");                          // Create a sdlWindow called "Hello, world!" and append into it.

	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
	ImGui::Checkbox("Demo Window", &b);      // Edit bools storing our sdlWindow open/close state
	ImGui::Checkbox("Another Window", &b);

	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		counter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}
