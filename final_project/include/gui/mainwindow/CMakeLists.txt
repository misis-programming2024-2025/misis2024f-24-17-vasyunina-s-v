file(GLOB MAINWINDOW_SOURCES
    "*.cpp"
    "*.hpp"
)

# Добавляем в родительский scope
set(GUI_SOURCES ${MAINWINDOW_SOURCES} PARENT_SCOPE)

# Отдельный таргет для тестирования
if(BUILD_TESTING)
    add_executable(MainWindowTests tests/MainWindowTests.cpp)
    target_link_libraries(MainWindowTests PRIVATE Qt5::Test)
    enable_testing()
    add_test(NAME MainWindowTests COMMAND MainWindowTests)
endif()