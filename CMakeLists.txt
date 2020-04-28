cmake_minimum_required(VERSION 3.13)
project(safe_sender)

set(CMAKE_CXX_STANDARD 17)


include_directories(lib) #for cryptopp and imgui
include_directories(lib/boost/asio/include)
include_directories(lib/boost/system/include)
include_directories(lib/boost/thread/include)
include_directories(lib/boost/test/include)
include_directories(lib/imgui)
include_directories(include)
add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(lib)
add_executable(safe_sender src/main.cpp)
target_link_libraries(safe_sender safe_sender_lib -lSDL2 -lGL -lGLEW imgui cryptopp-static boost_system boost_thread)