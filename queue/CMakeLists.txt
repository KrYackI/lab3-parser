file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_library(queue ${srcs} ${hdrs})
target_link_libraries(queue ${LIBRARY_DEPS})
