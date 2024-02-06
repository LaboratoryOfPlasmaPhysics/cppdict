
include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tpp/catch2)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2
    GIT_TAG devel
)
FetchContent_MakeAvailable(Catch2)

add_executable(basic_dict_ops basic_dict_ops.cpp)
target_include_directories(basic_dict_ops PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/../include)
target_compile_definitions(basic_dict_ops PRIVATE CATCH_CONFIG_NO_POSIX_SIGNALS)
target_link_libraries(basic_dict_ops PRIVATE Catch2::Catch2WithMain)
add_test(test_basic_dict_ops basic_dict_ops)

add_executable(stl_compatibility stl_compatibility.cpp)
target_include_directories(stl_compatibility PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/../include)
target_compile_definitions(stl_compatibility PRIVATE CATCH_CONFIG_NO_POSIX_SIGNALS)
target_link_libraries(stl_compatibility PRIVATE Catch2::Catch2WithMain)
add_test(test_stl_compatibility stl_compatibility)
