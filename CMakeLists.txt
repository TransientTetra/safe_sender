cmake_minimum_required(VERSION 3.13)
project(safe_sender)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/include/crypto++)
add_executable(safe_sender src/main.cpp src/controller/application.cpp include/controller/application.hpp src/view/window.cpp include/view/window.hpp src/model/sendable.cpp include/model/sendable.hpp src/model/encryption.cpp include/model/encryption.hpp src/model/text_message.cpp include/model/text_message.hpp src/model/encryption_aes.cpp include/model/encryption_aes.hpp src/model/raw_bytes.cpp include/model/raw_bytes.hpp src/model/encryptable.cpp include/model/encryptable.hpp src/model/file.cpp include/model/file.hpp src/model/file_metadata.cpp include/model/file_metadata.hpp include/constants.hpp src/model/encryption_sha_256.cpp include/model/encryption_sha_256.hpp src/model/encryption_rsa.cpp include/model/encryption_rsa.hpp)
target_link_libraries(safe_sender -lcrypto++)