add_library(tou STATIC)
target_sources(tou PRIVATE
    scheduler.cpp
)
target_include_directories(tou PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

