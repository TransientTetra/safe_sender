cmake_minimum_required(VERSION 3.13)
project(safe_sender)

set(CMAKE_CXX_STANDARD 17)

add_executable(safe_sender src/main.cpp src/controller/application.cpp include/controller/application.hpp src/view/window.cpp include/view/window.hpp)