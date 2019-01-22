cmake_minimum_required(VERSION 3.5)
project(cppdict-demo)


# Add a demo executable and link it against the library
add_executable(cppdict_demo demo1.cpp)
target_link_libraries(cppdict_demo
    cppdict  # Header-only library
)

