cmake_minimum_required(VERSION 3.15)

project(splot_fltk
        LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

#
# Format the project using the `clang-format` target (i.e: cmake --build build --target clang-format)
#
set(sources
        main.cpp
        render_fltk.cpp
)
set(headers
        plot_fltk.h
        render_fltk.h
)


add_clang_format_target()

#
# elements project settings
#

add_executable(splot_fltk
        ${sources}
        ${headers}
)

SET(FLTK_BUILD_TEST OFF)
SET(FLTK_BUILD_EXAMPLES OFF)
SET(FLTK_BUILD_SHARED_LIBS OFF)
SET(FLTK_BUILD_FLUID OFF)
SET(FLTK_BUILD_FLTK_OPTIONS OFF)

set(FLTK_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../../fltk-1.4.x")
add_subdirectory(${FLTK_ROOT} fltk)

target_link_libraries(splot_fltk fltk::fltk splot::splot)