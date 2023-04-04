include(FetchContent)
fetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.1
)
fetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

add_executable(df_test_arithmetic df_test_arithmetic.cpp)
target_link_libraries(df_test_arithmetic
        PRIVATE Catch2::Catch2WithMain
        PRIVATE df_operation
        PRIVATE df_logger
        PRIVATE df_interface)
catch_discover_tests(df_test_arithmetic)

add_executable(df_test_logic df_test_logic.cpp)
target_link_libraries(df_test_logic
        PRIVATE Catch2::Catch2WithMain
        PRIVATE df_operation
        PRIVATE df_logger
        PRIVATE df_interface)
catch_discover_tests(df_test_logic)

