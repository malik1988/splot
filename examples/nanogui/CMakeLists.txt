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

set(NANOGUI_BUILD_EXAMPLES OFF)
set(NANOGUI_BUILD_PYTHON OFF)
set(NANOGUI_BUILD_SHARED ON)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -D_LIBCPP_VERSION")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -stdlib=libc++")

set(NANOGUI_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../../nanogui")
add_subdirectory(${NANOGUI_ROOT} nanogui)

target_link_libraries(splot_nanogui
        splot::splot
        nanogui
)
file(COPY ${NANOGUI_ROOT}/resources/icons DESTINATION ${CMAKE_CURRENT_BINARY_DIR})