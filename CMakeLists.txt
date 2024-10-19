cmake_minimum_required(VERSION 3.22.0)

project(unit_test)

add_subdirectory(catch2)

add_executable(${PROJECT_NAME} "test.cpp" "my_list.h")

target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)
