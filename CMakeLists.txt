cmake_minimum_required(VERSION 3.31)
project(SysKaWu)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(SQLite3 REQUIRED)

add_executable(SysKaWu main.cpp
	szyfrowanie.cpp
	szyfrowanie.h
    db_test.cpp
    db_test.h)
    
target_link_libraries(SysKaWu sodium)
target_link_libraries(SysKaWu SQLite::SQLite3)
