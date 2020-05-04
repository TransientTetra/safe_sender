cmake_minimum_required(VERSION 3.13)
set(BINARY ${CMAKE_PROJECT_NAME}_tst)

set(CMAKE_CXX_STANDARD 17)

set(
        TST
        test_encryption_aes.cpp test_communicator.cpp)
set(TST ${TST})
include_directories(BINARY ../include)
add_executable(${BINARY} ${TST})
add_test(NAME ${BINARY} COMMAND ${BINARY})
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib boost_test cryptopp-static boost_system boost_thread)