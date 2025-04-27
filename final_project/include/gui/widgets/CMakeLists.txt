file(GLOB WIDGETS_SOURCES
    "*.cpp"
    "*.hpp"
)

# Добавляем в родительский scope
set(GUI_SOURCES ${GUI_SOURCES} ${WIDGETS_SOURCES} PARENT_SCOPE)