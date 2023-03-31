add_library(df_operation
        df_operation.h
        df_operation.c
        df_arithmetic.h
        df_arithmetic.c
        df_logic.h
        df_logic.c
        df_internal.h
        df_internal.c
        df_machine_learning.h
        df_machine_learning.cpp
        df_operations.h
        df_operations.c)
target_link_libraries(df_operation
        PRIVATE df_logger
        PRIVATE df_type)