cmake_minimum_required(VERSION 4.2)
project(Serwer)

set(CMAKE_CXX_STANDARD 20)

add_executable(Serwer main.cpp
        serverHeader.h
        serverBodies.cpp)
