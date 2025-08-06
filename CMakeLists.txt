cmake_minimum_required(VERSION 3.16)

project(fisjson VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
   printwidget.cpp
)

add_executable(fisjson
   main.cpp
   printwidget.cpp
)

target_link_libraries(fisjson PRIVATE Qt6::Widgets)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(fisjson)
endif()
