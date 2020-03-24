add_executable(basic_dict_ops basic_dict_ops.cpp)
target_include_directories(basic_dict_ops PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/../include)
add_test(test_basic_dict_ops basic_dict_ops)

add_executable(stl_compatibility stl_compatibility.cpp)
target_include_directories(stl_compatibility PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/../include)
add_test(test_stl_compatibility stl_compatibility)
