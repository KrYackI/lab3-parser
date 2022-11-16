file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_library(parser ${srcs} ${hdrs})
target_link_libraries(parser ${LIBRARY_DEPS})
