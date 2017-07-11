cmake_minimum_required(VERSION 3.7)
project(Jigsaw)

set(CMAKE_CXX_STANDARD 11)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
# Find the QtWidgets library
find_package(Qt5Widgets)

set(SOURCE_FILES
        gaming.cpp
        gaming.h
        gaming.ui
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        rankingdialog.cpp
        rankingdialog.h
        rankingdialog.ui)

add_executable(Jigsaw ${SOURCE_FILES})

# Use the Widgets module from Qt 5.
target_link_libraries(Jigsaw Qt5::Widgets)