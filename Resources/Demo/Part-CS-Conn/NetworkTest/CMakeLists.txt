cmake_minimum_required(VERSION 3.7)
project(NetworkTest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5Widgets)
find_package(Qt5Network)
set(SOURCE_FILES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui)

add_executable(NetworkTest ${SOURCE_FILES})
target_link_libraries(NetworkTest Qt5::Widgets)
target_link_libraries(NetworkTest Qt5::Network)