cmake_minimum_required(VERSION 3.14)
project(PoSt)

set(CMAKE_CXX_STANDARD 11)
set(INC_DIR /usr/local/include)
set(LINK_DIR /usr/local/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

find_package(OpenMP 4.5 REQUIRED)

include_directories(${INC_DIR})
link_directories(${LINK_DIR})

include_directories(include tinymt64/include)

add_subdirectory(tests)
add_subdirectory(src)
add_subdirectory(tinymt64)


