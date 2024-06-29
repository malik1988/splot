set(sources
        src/sploter.cpp
        src/sploter.h
        src/sploter_data.cpp

#        examples/eplot.cpp
#        examples/eplot.h
#        examples/main.cpp
#        examples/render_elements.cpp
#        examples/render_elements.h
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
)

set(test_sources
        src/tmp_test.cpp
)
