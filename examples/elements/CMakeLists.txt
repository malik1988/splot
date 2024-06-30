cmake_minimum_required(VERSION 3.15)
project(splot_elements
        LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

#
# Format the project using the `clang-format` target (i.e: cmake --build build --target clang-format)
#
set(sources
        main.cpp
        eplot.cpp
        render_elements.cpp
)
set(headers
        eplot.h
        render_elements.h
)


add_clang_format_target()

#
# elements project settings
#

add_executable(splot_elements
        ${sources}
        ${headers}
)

set(ELEMENTS_APP_PROJECT "splot-example")
set(ELEMENTS_APP_TITLE "splot example")
set(ELEMENTS_APP_COPYRIGHT "Copyright (c) 2024 Malik")
set(ELEMENTS_APP_ID "com.malik.splotexample")
set(ELEMENTS_APP_VERSION "1.0")

set(ELEMENTS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../../elements")
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${ELEMENTS_ROOT}/cmake")

include(ElementsConfigCommon)
add_subdirectory(${ELEMENTS_ROOT} elements)


# For your custom application icon on macOS or Windows see cmake/AppIcon.cmake module
include(AppIcon)
include(ElementsConfigApp)

target_link_libraries(splot_elements cycfi::elements splot::splot)

