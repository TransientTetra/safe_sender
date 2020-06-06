#include "view/main_frame.hpp"
#include "controller/application.hpp"

MainFrame::MainFrame(Window *window, const std::string &name)
: Frame(window, name), dirBrowser(ImGuiFileBrowserFlags_SelectDirectory)
{
	ipBuf[0] = '\0';
	msgBuf[0] = '\0';
	keyBuf[0] = '\0';
	currentCipherModeChoice = 0;
	fileBrowser.SetTitle("Choose file");
	dirBrowser.SetTitle("Choose directory to save file to");
	dirBrowserOpen = false;
}

void MainFrame::draw()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(window->getSDLWindow());
	ImGui::NewFrame();

	ImGui::Begin(name.c_str());
	ImGui::SetWindowSize(ImVec2(220 * 3, 330));
	ImGui::Columns(3);
	ImGui::SetColumnWidth(0, 220);
	ImGui::SetColumnWidth(1, 220);
	ImGui::SetColumnWidth(2, 220);
	ImGui::Text("Sending progress");
	ImGui::ProgressBar(application->getSendingProgress());

	ImGui::Text("Encryption progress");
	ImGui::ProgressBar(application->getEncryptionProgress());
	ImGui::NewLine();

	ImGui::Text("Cipher mode");
	if(ImGui::RadioButton("CFB", currentCipherModeChoice == 0)) currentCipherModeChoice = 0;
	if(ImGui::RadioButton("CBC", currentCipherModeChoice == 1)) currentCipherModeChoice = 1;
	if(ImGui::RadioButton("ECB", currentCipherModeChoice == 2)) currentCipherModeChoice = 2;
	if(ImGui::RadioButton("OFB", currentCipherModeChoice == 3)) currentCipherModeChoice = 3;
	application->setCipherMode(currentCipherModeChoice);
	ImGui::NewLine();

	ImGui::Text("Input IP to connect to");
	ImGui::InputText("", ipBuf, sizeof(ipBuf) / sizeof(char));
	if (ImGui::Button("Connect"))
	{
		application->connect(std::string(ipBuf));
	}

	ImGui::NextColumn();
	ImGui::Text("Write your message");
	ImGui::InputTextMultiline("##msgwin", msgBuf, sizeof(msgBuf) / sizeof(char),
		ImVec2(200, 250));


	ImGui::NextColumn();
	ImGui::Text("Connected to:");
	ImGui::Text("%s", application->getIP().c_str());
	if (ImGui::Button("Disconnect")) application->disconnect();

	ImGui::NewLine();
	ImGui::Text("Chosen file:");
	ImGui::Text("%s", std::filesystem::path(application->getChosenFile()).filename().c_str());
	if (ImGui::Button("Browse"))
	{
		fileBrowser.Open();
	}

	ImGui::NewLine();
	ImGui::NewLine();
	if (ImGui::Button("Encrypt and send message"))
	{
		application->encryptAndSendMsg(std::string(msgBuf), std::string(keyBuf));
	}
	if (ImGui::Button("Encrypt and send file"))
	{
		application->encryptAndSendFile(std::string(keyBuf));
	}

	ImGui::End();
	fileBrowser.Display();
	if (fileBrowser.HasSelected())
	{
		application->setFilePath(fileBrowser.GetSelected().string());
		fileBrowser.ClearSelected();
	}
	dirBrowser.Display();
	if (dirBrowser.HasSelected())
	{
		dirPath = dirBrowser.GetSelected().string();
		dirBrowser.ClearSelected();
		dirBrowserOpen = false;
	}
	//ImGui::EndFrame();
}

void MainFrame::openDirBrowser()
{
	dirBrowserOpen = true;
	dirBrowser.Open();
}

bool MainFrame::isDirBrowserOpen() const
{
	return dirBrowserOpen;
}

const std::string &MainFrame::getDirPath() const
{
	return dirPath;
}
