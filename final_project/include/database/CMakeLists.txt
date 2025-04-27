# Библиотека для работы с БД
add_library(DatabaseLib STATIC
    database.cpp
    database.hpp
)

find_package(SQLite3 REQUIRED)
target_link_libraries(DatabaseLib PRIVATE SQLite::SQLite3)
target_include_directories(DatabaseLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)