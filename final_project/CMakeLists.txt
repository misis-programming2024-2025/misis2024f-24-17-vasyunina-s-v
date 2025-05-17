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

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Svg)

# Добавляем ресурсы ДО создания исполняемого файла
set(RESOURCES_DIR "${CMAKE_SOURCE_DIR}/include/gui/resources")
qt_add_resources(RESOURCE_FILES "resources.qrc")

add_subdirectory(include/task)
add_subdirectory(include/taskmanager)
add_subdirectory(include/database)
add_subdirectory(include/gui)

add_executable(TaskManager include/main.cpp)  

target_sources(TaskManager PRIVATE ${RESOURCE_FILES})

target_link_libraries(TaskManager PRIVATE
    GUILib
    DatabaseLib
    TaskLib
    TaskManagerLib
    Qt6::Core
    Qt6::Widgets
    Qt6::Svg
)
