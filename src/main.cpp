#include <iostream>
#include "controller/application.hpp"
#include "constants.hpp"
#include "view/main_frame.hpp"
#include "model/communication/sender.hpp"
#include "model/communication/receiver.hpp"
#include "model/encryption/encryption_aes.hpp"

// Main code
int main(int argc, char** argv)
{
	Application application(DEFAULT_WINDOW_TITLE);
	application.run();
	return 0;
}
