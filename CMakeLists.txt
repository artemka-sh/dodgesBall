cmake_minimum_required(VERSION 3.0)

project(pong VERSION 1.0)

add_executable(pong main.cpp)
target_link_libraries(pong sfml-graphics sfml-window sfml-system)
