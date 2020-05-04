#include "view/main_frame.hpp"
#include "constants.hpp"

MainFrame::MainFrame(Window *window, const std::string &name, ModifiableFields* modifiableFields)
: Frame(window, name), applicationFields(modifiableFields)
{
}

void MainFrame::draw(Receiver *receiver, Sender *sender)
{
	Frame::draw();

	ImGui::Begin(name.c_str());
	ImGui::SetWindowSize(ImVec2(220 * 3, 380));
	ImGui::Columns(3);
	ImGui::SetColumnWidth(0, 220);
	ImGui::SetColumnWidth(1, 220);
	ImGui::SetColumnWidth(2, 220);
	ImGui::Text("Sending progress");
	ImGui::ProgressBar(applicationFields->encryptionProgress);

	ImGui::Text("Encryption progress");
	ImGui::ProgressBar(applicationFields->sendingProgress);

	ImGui::Text("Cipher mode");
	static int currentChoice = 0;
	if(ImGui::RadioButton("CFB", currentChoice == 0)) currentChoice = 0;
	if(ImGui::RadioButton("CBC", currentChoice == 1)) currentChoice = 1;
	if(ImGui::RadioButton("ECB", currentChoice == 2)) currentChoice = 2;
	if(ImGui::RadioButton("OFB", currentChoice == 3)) currentChoice = 3;
	applicationFields->cipherMode = static_cast<CipherMode>(currentChoice);

	static char ipBuf[16];
	ImGui::Text("Input IP to connect to");
	ImGui::InputText("", ipBuf, sizeof(ipBuf) / sizeof(char));
	if (ImGui::Button("Connect"))
	{
		applicationFields->ipToSendTo = ipBuf;
		sender = new Sender(applicationFields->ipToSendTo, DEFAULT_PORT);
		sender->connect();
	}

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
	ImGui::Text("%s", applicationFields->ipToSendTo.c_str());
	if (ImGui::Button("Disconnect")) applicationFields->ipToSendTo = "None";

	ImGui::NewLine();
	ImGui::Text("Chosen file:");
	ImGui::Text("None");
	if (ImGui::Button("Browse"));

	ImGui::NewLine();
	ImGui::NewLine();
	if (ImGui::Button("Encrypt and send message"))
	{
		applicationFields->message = msgBuf;
		applicationFields->key = keyBuf;
		TextMessage *txt = new TextMessage(applicationFields->message);
		InitializationVector *iv = new InitializationVector("0");
		EncryptionKey *key = new EncryptionKey(applicationFields->key);
		sender->sendTxtMsg(*txt, *key, *iv, false);
		delete txt;
		delete iv;
		delete key;
	}
	if (ImGui::Button("Encrypt and send file"))
	{
		//todo here file picker
		applicationFields->key = keyBuf;
	}

	ImGui::End();
}
