add_executable(narity-test narity-test.c ../dfinterface.c)
target_link_libraries(narity-test PUBLIC woof)
target_include_directories(narity-test PUBLIC "./include")

add_executable(cond-test cond-test.c ../dfinterface.c)
target_link_libraries(cond-test PUBLIC woof)
target_include_directories(cond-test PUBLIC "./include")