include_directories(imgui)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
set(
        IMGUI_SRC

        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_widgets.cpp
        imgui/examples/imgui_impl_sdl.cpp
        imgui/examples/imgui_impl_opengl3.cpp
)
set(IMGUI_SRC ${IMGUI_SRC})
add_library(imgui ${IMGUI_SRC})