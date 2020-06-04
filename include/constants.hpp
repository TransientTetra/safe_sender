#ifndef SAFE_SENDER_CONSTANTS_HPP
#define SAFE_SENDER_CONSTANTS_HPP

#define DEFAULT_PORT 9898
#define DEFAULT_WINDOW_TITLE "Safe Sender"
#define DEFAULT_WINDOW_WIDTH 900
#define DEFAULT_WINDOW_HEIGHT 600

#define PACKET_CHAR_BUFFER_SIZE 64
#define DEFAULT_IV "0000000000000000"
#define DEFAULT_IV_SIZE sizeof(DEFAULT_IV) - 1
#define DEFAULT_SESSION_KEY_SIZE 32
#define DEFAULT_RSA_KEY_SIZE 3072

#endif //SAFE_SENDER_CONSTANTS_HPP
