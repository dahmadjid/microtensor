cmake_minimum_required(VERSION 3.20)

project(micrograd VERSION 1.0.0 LANGUAGES CXX)

if (WIN32)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -fsanitize=address -std=c++20)
    add_link_options(-fsanitize=address)
    set(CMAKE_CXX_FLAGS "-fuse-ld=lld")
endif()

add_subdirectory(libs)
add_subdirectory(src)
file(COPY data DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/src")