cmake_minimum_required(VERSION 2.6)
project(opt)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_executable(run_unit_tests opt.cpp opt_test.cpp)

target_link_libraries(run_unit_tests -lgtest -lgtest_main -lpthread)

