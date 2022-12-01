file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_library(stack_queue ${srcs} ${hdrs})
target_link_libraries(stack_queue ${LIBRARY_DEPS})
