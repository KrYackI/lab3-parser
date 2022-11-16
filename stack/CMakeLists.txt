file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_library(stack ${srcs} ${hdrs})
target_link_libraries(stack ${LIBRARY_DEPS})
