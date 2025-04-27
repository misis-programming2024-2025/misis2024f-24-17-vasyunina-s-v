# gui/CMakeLists.txt
cmake_minimum_required(VERSION 3.5)

project(GUI LANGUAGES CXX)

# Настройка автоматической обработки Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 1. Собираем список исходников
file(GLOB GUI_SOURCES
    "*.cpp"
    "*.hpp"
    "mainwindow/*.cpp"
    "mainwindow/*.hpp"
    "widgets/*.cpp"
    "widgets/*.hpp"
)

# 2. Ресурсы (убедитесь что файл существует)
set(RESOURCE_FILES 
    "resources.qrc"
)

# 3. Создаем библиотеку
add_library(GUILib STATIC
    ${GUI_SOURCES}
    ${RESOURCE_FILES}
)

# 4. Подключаем зависимости
find_package(Qt5 REQUIRED COMPONENTS Widgets Svg)

target_link_libraries(GUILib PRIVATE
    Qt5::Widgets
    Qt5::Svg
)

target_include_directories(GUILib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)