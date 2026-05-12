cmake_minimum_required(VERSION 3.31)
project(SysKaWu)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SQLite3 REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Quick)

add_executable(SysKaWu main.cpp
    qml/resources.qrc
    qml/manager.cpp
    qml/manager.h
	backend/passwords.cpp
	backend/passwords.h
    backend/connection.cpp
    backend/connection.h
    backend/serverHeader.h
    backend/serverBodies.cpp
    backend/queryResponse.h
    )

    
target_link_libraries(SysKaWu sodium)
target_link_libraries(SysKaWu SQLite::SQLite3)
target_link_libraries(SysKaWu Qt6::Core)
target_link_libraries(SysKaWu Qt6::Quick)
set_property(TARGET SysKaWu PROPERTY AUTOMOC ON)
set_property(TARGET SysKaWu PROPERTY AUTORCC ON)

