# Настройка GUI модуля
qt_add_executable(TaskManagerGUI
    mainwindow/MainWindow.cpp
    widgets/TaskWidget.cpp
    dialogs/TaskDialog.cpp
    resources/resources.qrc  # Файл ресурсов
)

target_link_libraries(TaskManagerGUI PRIVATE
    Qt5::Widgets
    Qt5::Svg
    TaskManager
)

# Создание файла ресурсов
qt_add_resources(RESOURCES_PREFIX "/"
    RESOURCES
    resources/icons/add.svg
    resources/icons/edit.svg
    resources/styles/main.qss
)

qt_add_resources(GUI_RESOURCES "resources.qrc")
target_sources(TaskManagerGUI PRIVATE ${GUI_RESOURCES})

# Подключение модулей Qt
find_package(Qt5 REQUIRED COMPONENTS Widgets Svg)

# Подключение заголовочных файлов
target_include_directories(TaskManagerGUI PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)