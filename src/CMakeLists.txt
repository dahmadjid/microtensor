add_executable(micrograd main.cpp files.cpp)

target_link_libraries(micrograd fmt)

target_include_directories(micrograd PUBLIC fmt)
