cmake_minimum_required(VERSION 3.14)
project(PoSt)

set(CMAKE_CXX_STANDARD 11)
set(INC_DIR /usr/local/include)
set(LINK_DIR /usr/local/lib)

include_directories(${INC_DIR})
link_directories(${LINK_DIR})

add_subdirectory(tests)