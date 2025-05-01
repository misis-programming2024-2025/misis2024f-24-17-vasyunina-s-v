# Модель задачи
add_library(TaskLib STATIC
    task.cpp
    task.hpp
)

target_include_directories(TaskLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)