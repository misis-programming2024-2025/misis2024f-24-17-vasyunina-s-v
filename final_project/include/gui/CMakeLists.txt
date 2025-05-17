cmake_minimum_required(VERSION 3.5)

project(GUI LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

file(GLOB GUI_SOURCES
    "*.cpp"
    "*.hpp"
    "mainwindow/*.cpp"
    "mainwindow/*.hpp"
    "widgets/*.cpp"
    "widgets/*.hpp"
    "dialogs/*.cpp"
    "dialogs/*.hpp"
)

add_library(GUILib STATIC
    ${GUI_SOURCES}
    ${GUI_HEADERS}
    ${GUI_UI_HEADERS}
    ${GUI_RESOURCES}
)

find_package(Qt6 REQUIRED COMPONENTS Widgets Svg)

target_link_libraries(GUILib PRIVATE
    Qt6::Widgets
    Qt6::Svg
    TaskManagerLib
    DatabaseLib
)

target_include_directories(GUILib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)