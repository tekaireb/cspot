add_subdirectory(tests)
add_subdirectory(logger_system)
add_subdirectory(operation_system)
add_subdirectory(type_system)

add_library(df_interface
        df.h
        df_interface.cpp
        df_interface.h)
target_link_libraries(df_interface
        PRIVATE woof
        PRIVATE df_operation)

add_handler(output_handler output_handler.cpp)
target_link_libraries(output_handler
        PRIVATE df_interface
        PRIVATE df_type)

add_handler(subscription_event_handler subscription_event_handler.cpp)
target_link_libraries(subscription_event_handler
        PRIVATE df_interface
        PRIVATE df_type
        PRIVATE df_operation)