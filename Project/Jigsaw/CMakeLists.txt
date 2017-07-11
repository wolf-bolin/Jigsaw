cmake_minimum_required(VERSION 3.7)
project(Jigsaw)

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
        mainwindow.ui
        gamelogic.cpp
        gamelogic.h
        rankbrowser.cpp
        rankbrowser.h
        rankbrowser.ui
        setting.cpp
        setting.h
        setting.ui
        success.cpp
        success.h
        success.ui)
qt5_add_resources(qrc_FILES picture/picture.qrc)
add_executable(Jigsaw ${SOURCE_FILES} ${qrc_FILES})
target_link_libraries(Jigsaw Qt5::Widgets)
target_link_libraries(Jigsaw Qt5::Network)