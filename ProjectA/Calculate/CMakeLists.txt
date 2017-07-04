cmake_minimum_required(VERSION 3.7)
project(CalculateCL)

set(CMAKE_CXX_STANDARD 11)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
# Find the QtWidgets library
find_package(Qt5Widgets)

set(SOURCE_FILES
        calculate.cpp
        calculate.h
        global.cpp
        global.h
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui)

add_executable(CalculateCL ${SOURCE_FILES})

# Use the Widgets module from Qt 5.
target_link_libraries(CalculateCL Qt5::Widgets)