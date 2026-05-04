cmake_minimum_required(VERSION 3.31)
project(SysKaWu)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(SQLite3 REQUIRED)

add_executable(SysKaWu main.cpp
	backend/szyfrowanie.cpp
	backend/szyfrowanie.h
    backend/connection.cpp
    backend/connection.h
    backend/serverHeader.h
    backend/serverBodies.cpp)

    
target_link_libraries(SysKaWu sodium)
target_link_libraries(SysKaWu SQLite::SQLite3)
