set(sources
        src/sploter.cpp
        src/sploter.h
        src/sploter_data.cpp
        src/sploter_factory.cpp
)

set(exe_sources
        examples/eplot.cpp
        examples/eplot.h
        examples/main.cpp
        examples/render_elements.cpp
        examples/render_elements.h
        ${sources}
)

set(headers
        include/irender.h
        include/isploter.h
        include/sploter_data.h
        include/sploter_factory.h
)

set(test_sources
        src/tmp_test.cpp
)
