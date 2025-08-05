cmake_minimum_required(VERSION 3.16)

project(fisjson VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# List only source (.cpp) files here
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
)

# This processes the .ui file and generates ui_mainwindow.h
qt6_wrap_ui(UI_HEADERS ui/mainwindow.ui)

add_executable(fisjson
    ${PROJECT_SOURCES}
    ${UI_HEADERS}
    mainwindow.h mainwindow.ui
)

target_link_libraries(fisjson PRIVATE Qt6::Widgets)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(fisjson)
endif()
