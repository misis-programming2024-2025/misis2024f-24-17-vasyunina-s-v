# Менеджер задач
add_library(TaskManagerLib STATIC
    taskmanager.cpp
    taskmanager.hpp
)

target_link_libraries(TaskManagerLib PRIVATE 
    TaskLib
    DatabaseLib
)

target_include_directories(TaskManagerLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)