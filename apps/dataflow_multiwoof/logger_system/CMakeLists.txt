add_library(df_logger
        df_logger.h
        df_logger.c
        df_operation_logger.c
        df_operation_logger.h)
target_link_libraries(df_logger
        PRIVATE df_type)