cmake_minimum_required(VERSION 3.20)
project(The_Game_Of_TRON)

set(CMAKE_CXX_STANDARD 20)

include_directories(include/)

add_executable(The_Game_Of_Tron
        src/Main.cpp
        src/Node.cpp
)