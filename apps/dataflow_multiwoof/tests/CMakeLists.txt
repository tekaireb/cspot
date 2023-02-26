add_executable(df-filter-test df-filter-test.cpp ../dfinterface.cpp)
target_link_libraries(df-filter-test PUBLIC woof)
target_include_directories(df-filter-test PUBLIC "./include")

add_executable(df-matmul-test df-matmul-test.cpp ../dfinterface.cpp)
target_link_libraries(df-matmul-test PUBLIC woof)
target_include_directories(df-matmul-test PUBLIC "./include")

add_executable(df-multi-machine-test df-multi-machine-test.cpp ../dfinterface.cpp)
target_link_libraries(df-multi-machine-test PUBLIC woof)
target_include_directories(df-multi-machine-test PUBLIC "./include")

add_executable(df-namespace-graphviz-test df-namespace-graphviz-test.cpp ../dfinterface.cpp)
target_link_libraries(df-namespace-graphviz-test PUBLIC woof)
target_include_directories(df-namespace-graphviz-test PUBLIC "./include")

add_executable(df-namespace-test df-namespace-test.cpp ../dfinterface.cpp)
target_link_libraries(df-namespace-test PUBLIC woof)
target_include_directories(df-namespace-test PUBLIC "./include")

add_executable(df-selector-test df-selector-test.cpp ../dfinterface.cpp)
target_link_libraries(df-selector-test PUBLIC woof)
target_include_directories(df-selector-test PUBLIC "./include")

add_executable(df-simple-test df-simple-test.cpp ../dfinterface.cpp)
target_link_libraries(df-simple-test PUBLIC woof)
target_include_directories(df-simple-test PUBLIC "./include")

add_executable(df-square-root-test df-square-root-test.cpp ../dfinterface.cpp)
target_link_libraries(df-square-root-test PUBLIC woof)
target_include_directories(df-square-root-test PUBLIC "./include")

add_executable(df-static-maps-test df-static-maps-test.cpp ../dfinterface.cpp)
target_link_libraries(df-static-maps-test PUBLIC woof)
target_include_directories(df-static-maps-test PUBLIC "./include")

add_executable(df-quadratic-test df-quadratic-test.cpp ../dfinterface.cpp)
target_link_libraries(df-quadratic-test PUBLIC woof)
target_include_directories(df-quadratic-test PUBLIC "./include")

add_executable(df-quadratic-multi-machine-test df-quadratic-multi-machine-test.cpp ../dfinterface.cpp)
target_link_libraries(df-quadratic-multi-machine-test PUBLIC woof)
target_include_directories(df-quadratic-multi-machine-test PUBLIC "./include")

add_executable(df-knn-test df-knn-test.cpp ../dfinterface.cpp)
target_link_libraries(df-knn-test PUBLIC woof)
target_include_directories(df-knn-test PUBLIC "./include")

add_executable(df-online-linreg-multinode-test df-online-linreg-multinode-test.cpp ../dfinterface.cpp)
target_link_libraries(df-online-linreg-multinode-test PUBLIC woof)
target_include_directories(df-online-linreg-multinode-test PUBLIC "./include")

add_executable(df-online-linreg-test df-online-linreg-test.cpp ../dfinterface.cpp)
target_link_libraries(df-online-linreg-test PUBLIC woof)
target_include_directories(df-online-linreg-test PUBLIC "./include")