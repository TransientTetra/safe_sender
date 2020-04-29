#include "view/main_frame.hpp"

MainFrame::MainFrame(Window *window, const std::string &name, std::string *ip, float* encryptionProgress,
	float* sendingProgress)
: Frame(window, name)
{
	applicationIPToSendTo = ip;
	applicationEncryptionProgress = encryptionProgress;
	applicationSendingProgress = sendingProgress;
}

void MainFrame::draw()
{
	Frame::draw();

	ImGui::Begin(name.c_str());
	ImGui::Columns(3);
	ImGui::SetColumnWidth(0, 220);
	ImGui::SetColumnWidth(1, 220);
	ImGui::SetColumnWidth(2, 220);
	ImGui::Text("Sending progress");
	ImGui::ProgressBar(*applicationEncryptionProgress);

	ImGui::Text("Encryption progress");
	ImGui::ProgressBar(*applicationSendingProgress);

	ImGui::Text("Cipher mode");
	static int currentChoice = 0;
	if(ImGui::RadioButton("CFB", currentChoice == 0)) currentChoice = 0;
	if(ImGui::RadioButton("CBC", currentChoice == 1)) currentChoice = 1;
	if(ImGui::RadioButton("ECB", currentChoice == 2)) currentChoice = 2;
	if(ImGui::RadioButton("OFB", currentChoice == 3)) currentChoice = 3;

	static char ipBuf[16];
	ImGui::Text("Input IP to connect to");
	ImGui::InputText("", ipBuf, sizeof(ipBuf) / sizeof(char));
	if (ImGui::Button("Connect")) *applicationIPToSendTo = ipBuf;

	ImGui::NextColumn();
	static char msgBuf[256];
	ImGui::Text("Write your message");
	ImGui::InputTextMultiline("##msgwin", msgBuf, sizeof(msgBuf) / sizeof(char),
		ImVec2(200, 250));

	static char keyBuf[256];
	ImGui::Text("Enter encryption key");
	ImGui::Text("leave empty for no encryption");
	ImGui::InputText("##key", keyBuf, sizeof(keyBuf) / sizeof(char));

	ImGui::NextColumn();
	ImGui::Text("Connected to:");
	ImGui::Text("%s", applicationIPToSendTo->c_str());
	if (ImGui::Button("Disconnect")) *applicationIPToSendTo = "None";

	ImGui::NewLine();
	ImGui::Text("Chosen file:");
	ImGui::Text("None");
	if (ImGui::Button("Browse"));

	ImGui::NewLine();
	ImGui::NewLine();
	if (ImGui::Button("Encrypt and send message"));
	if (ImGui::Button("Encrypt and send file"));

	ImGui::End();
}
