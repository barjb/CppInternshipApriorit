cmake_minimum_required(VERSION 3.24)
project(testing)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(googletest-main)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(
    main_test
    main_test.cc
)

add_executable(
    tdd_task2
    tdd.cpp
)

target_link_libraries(main_test gtest gtest_main)
add_test(main_test main_test)

target_link_libraries(tdd_task2 gtest gtest_main)
add_test(tdd_task2 main_test)