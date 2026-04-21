cmake_minimum_required(VERSION 3.31)
project(SysKaWu)

set(CMAKE_CXX_STANDARD 20)

add_executable(SysKaWu main.cpp
	szyfrowanie.cpp
	szyfrowanie.h)
