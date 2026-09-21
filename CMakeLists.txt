cmake_minimum_required(VERSION 3.25)
project(tou)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 23)

add_subdirectory(src)
add_subdirectory(bench)

if (TEST)
    add_subdirectory(tests)
endif()
