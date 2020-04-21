cmake_minimum_required(VERSION 3.13)
project(safe_sender)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/include/crypto++)
include_directories(/usr/include/asio)
add_executable(safe_sender src/main.cpp src/controller/application.cpp include/controller/application.hpp src/view/window.cpp include/view/window.hpp src/model/communication/sendable.cpp include/model/communication/sendable.hpp include/model/encryption/encryption.hpp src/model/text_message.cpp include/model/text_message.hpp src/model/encryption/encryption_aes.cpp include/model/encryption/encryption_aes.hpp src/model/raw_bytes.cpp include/model/raw_bytes.hpp src/model/encryption/encryptable.cpp include/model/encryption/encryptable.hpp src/model/file.cpp include/model/file.hpp src/model/file_metadata.cpp include/model/file_metadata.hpp include/constants.hpp src/model/encryption/encryption_sha_256.cpp include/model/encryption/encryption_sha_256.hpp src/model/encryption/encryption_rsa.cpp include/model/encryption/encryption_rsa.hpp src/model/encryption/encryption.cpp src/model/encryption/encryption_key.cpp include/model/encryption/encryption_key.hpp src/model/initialization_vector.cpp include/model/initialization_vector.hpp src/model/data_container.cpp include/model/data_container.hpp src/model/communication/receiver.cpp include/model/communication/receiver.hpp src/model/communication/sender.cpp include/model/communication/sender.hpp)
target_link_libraries(safe_sender -lcrypto++ -lboost_system -lboost_thread -pthread)