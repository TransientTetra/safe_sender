cmake_minimum_required(VERSION 3.13)
set(BINARY ${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(
        SRC
        controller/application.cpp
        view/window.cpp
        model/text_message.cpp
        model/encryption/encryption_aes.cpp
        model/raw_bytes.cpp
        model/encryption/encryptable.cpp
        model/file.cpp
        model/encryption/encryption_sha_256.cpp
        model/encryption/encryption_rsa.cpp
        model/encryption/encryption.cpp
        model/encryption/encryption_key.cpp
        model/initialization_vector.cpp
        model/data_container.cpp
        model/communication/receiver.cpp
        model/communication/sender.cpp
        model/communication/sendable.cpp
        model/communication/communicator.cpp
        view/frame.cpp
        view/main_frame.cpp model/communication/receiver_session.cpp ../include/model/communication/receiver_session.hpp view/info_frame.cpp ../include/view/info_frame.hpp ../include/view/yes_no_frame.cpp ../include/view/yes_no_frame.hpp ../include/model/communication/session.cpp ../include/model/communication/session.hpp model/communication/sender_session.cpp ../include/model/communication/sender_session.hpp)
set(SRC ${SRC})

include_directories(../include BINARY)
add_library(${BINARY}_lib STATIC ${SRC})