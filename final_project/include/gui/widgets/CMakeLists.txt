file(GLOB WIDGETS_SOURCES
    "*.cpp"
    "*.hpp"
)

set(GUI_SOURCES ${GUI_SOURCES} ${WIDGETS_SOURCES} PARENT_SCOPE)