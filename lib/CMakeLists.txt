include_directories(imgui)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/include/SDL2")
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