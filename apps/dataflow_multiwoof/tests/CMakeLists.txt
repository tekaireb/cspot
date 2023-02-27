add_executable(multiwoof-test multiwoof-test.cpp ../dfinterface.cpp)
target_link_libraries(multiwoof-test PUBLIC woof)
target_include_directories(multiwoof-test PUBLIC "./include")

add_executable(baseline-regression baseline-regression.cpp)