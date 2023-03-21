add_subdirectory(tests)
add_subdirectory(logger_system)
add_subdirectory(operation_system)
add_subdirectory(type_system)

add_handler(output_handler output_handler.cpp dfinterface.cpp)
target_link_libraries(output_handler PUBLIC woof)
target_include_directories(output_handler PUBLIC "./include")

add_handler(subscription_event_handler subscription_event_handler.cpp dfinterface.cpp)
target_link_libraries(subscription_event_handler PUBLIC woof)
target_include_directories(subscription_event_handler PUBLIC "./include")