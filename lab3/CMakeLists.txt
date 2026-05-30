cmake_minimum_required(VERSION 3.16)

project(lab3 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

qt_add_executable(lab3
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    httpclient.h
    httpclient.cpp

    car.h
    icar_adapter.h
    car_json_adapter.h
    car_json_adapter.cpp
)

target_link_libraries(lab3 PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
)