cmake_minimum_required(VERSION 3.31)
project(SysKaWu)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(SysKaWu main.cpp
	szyfrowanie.cpp
	szyfrowanie.h)
target_link_libraries(SysKaWu sodium)
