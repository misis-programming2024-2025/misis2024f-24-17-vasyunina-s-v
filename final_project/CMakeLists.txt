cmake_minimum_required(VERSION 3.5)
project(TaskManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

add_subdirectory(include/database)
add_subdirectory(include/task)
add_subdirectory(include/taskmanager)
add_subdirectory(include/gui)

add_executable(TaskManager src/main.cpp)  
target_link_libraries(TaskManager PRIVATE
    DatabaseLib
    TaskLib
    TaskManagerLib
    GuiLib
)

