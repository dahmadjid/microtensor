add_executable(microtensor main.cpp files.cpp)

target_link_libraries(microtensor fmt)

target_include_directories(microtensor PUBLIC fmt)
