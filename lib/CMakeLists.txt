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
        imgui-filebrowser/imfilebrowser.h
)
set(IMGUI_SRC ${IMGUI_SRC})
add_library(imgui ${IMGUI_SRC})

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_subdirectory(googletest)
endif()