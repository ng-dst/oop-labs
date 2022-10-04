set(core_SRCS LemniscateBooth.cpp LemniscateBooth.h CurveType.h)

add_library(core ${core_SRCS})
add_executable(exe main.cpp)
target_link_libraries(exe core)
