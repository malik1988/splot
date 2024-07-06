cmake_minimum_required(VERSION 3.15)

project(splot_nanogui
        LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

#
# Format the project using the `clang-format` target (i.e: cmake --build build --target clang-format)
#
set(sources
        main.cpp
        render_nanogui.cpp
        nplot.cpp
)
set(headers
        render_nanogui.h
        nplot.h
)


add_clang_format_target()

#
# elements project settings
#

add_executable(splot_nanogui
        ${sources}
        ${headers}
)


set(NANOGUI_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../../nanogui")
add_subdirectory(${NANOGUI_ROOT} nanogui)

target_link_libraries(splot_nanogui nanogui splot::splot)