# Модель задачи
add_library(TaskLib STATIC
    Task.cpp
    Task.hpp
)

target_include_directories(TaskLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)