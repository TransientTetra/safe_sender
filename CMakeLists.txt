cmake_minimum_required(VERSION 3.13)
project(safe_sender)

set(CMAKE_CXX_STANDARD 17)

find_library(SDL2_LIBRARY NAME SDL2)
find_library(GL_LIBRARY NAME GL)
find_library(GLEW_LIBRARY NAME GLEW)
find_package(Threads REQUIRED)

include_directories(lib)
include_directories(lib/imgui)
include_directories(include)
add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(lib)
add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}_lib Threads::Threads SDL2 GL GLEW -lcrypto++ imgui)