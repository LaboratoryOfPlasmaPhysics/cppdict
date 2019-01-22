
cmake_minimum_required(VERSION 3.0)
project(cppdict)
set(CMAKE_CXX_STANDARD 17)
set(CPPDICT_INCLUDE_DIR,  ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(cppdict INTERFACE)
target_include_directories(cppdict INTERFACE $<BUILD_INTERFACE:${CPPDICT_INCLUDE_DIR}>
                                             $<INSTALL_INTERFACE:include>)


add_subdirectory(test)

