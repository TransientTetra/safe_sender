cmake_minimum_required(VERSION 3.13)
project(boost_test)

set(CMAKE_CXX_STANDARD 17)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test/src)
set(
        BOOST_TEST_SRC

        ${SRC_DIR}/compiler_log_formatter.cpp
        ${SRC_DIR}/debug.cpp
        ${SRC_DIR}/decorator.cpp
        ${SRC_DIR}/execution_monitor.cpp
        ${SRC_DIR}/framework.cpp
        ${SRC_DIR}/junit_log_formatter.cpp
        ${SRC_DIR}/plain_report_formatter.cpp
        ${SRC_DIR}/progress_monitor.cpp
        ${SRC_DIR}/results_collector.cpp
        ${SRC_DIR}/results_reporter.cpp
        ${SRC_DIR}/test_framework_init_observer.cpp
        ${SRC_DIR}/test_main.cpp
        ${SRC_DIR}/test_tools.cpp
        ${SRC_DIR}/test_tree.cpp
        ${SRC_DIR}/unit_test_log.cpp
        ${SRC_DIR}/unit_test_main.cpp
        ${SRC_DIR}/unit_test_monitor.cpp
        ${SRC_DIR}/unit_test_parameters.cpp
        ${SRC_DIR}/xml_log_formatter.cpp
        ${SRC_DIR}/xml_report_formatter.cpp
)
set(BOOST_TEST_SRC ${BOOST_TEST_SRC})

add_library(boost_test ${BOOST_TEST_SRC})