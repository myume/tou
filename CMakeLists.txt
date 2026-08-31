cmake_minimum_required(VERSION 3.25)
project(tou)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 23)

add_library(tou STATIC)
add_subdirectory(src)
