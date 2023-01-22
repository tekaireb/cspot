add_subdirectory(tests)

#add_library(dfoperation dfoperation.c)
#target_link_libraries(dfoperation PUBLIC woof)
#target_include_directories(dfoperation PUBLIC "./include")

# TODO: fix wf->shared->filename
add_executable(operation_handler operation_handler.cpp)
target_link_libraries(operation_handler PUBLIC woof)
target_include_directories(operation_handler PUBLIC "./include")
