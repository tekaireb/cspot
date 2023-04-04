set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_subdirectory(operation_system)
add_subdirectory(type_system)

add_executable(multinode_regression multinode_regression.cpp)
target_link_libraries(multinode_regression
        PRIVATE df_interface
        PRIVATE df_type
        PRIVATE df_operation)

add_executable(tests
        tests.cpp
        arithmetic_tests.cpp
        conditional_tests.cpp
        namespace_tests.cpp
        loop_tests.cpp)
target_link_libraries(tests
        PRIVATE df_interface
        PRIVATE df_type
        PRIVATE df_operation)

add_executable(baseline-regression baseline-regression.cpp)