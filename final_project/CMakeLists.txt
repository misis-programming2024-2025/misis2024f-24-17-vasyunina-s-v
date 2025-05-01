cmake_minimum_required(VERSION 3.5)
project(TaskManager LANGUAGES CXX)

include_directories(
    ${CMAKE_SOURCE_DIR}/final_project/include
    ${Qt5Core_INCLUDE_DIRS}
)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Svg) 

add_subdirectory(include/task)
add_subdirectory(include/taskmanager)
add_subdirectory(include/database)
add_subdirectory(include/gui)

add_executable(TaskManager include/main.cpp)  
target_link_libraries(TaskManager PRIVATE
    GUILib
    DatabaseLib
    TaskLib
    TaskManagerLib
    Qt5::Core
    Qt5::Widgets
    Qt5::Svg
)
