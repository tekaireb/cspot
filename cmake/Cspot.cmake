cmake_minimum_required(VERSION 3.2)
project(cspot C)

set(DIR_OF_CSPOT_CMAKE ${CMAKE_CURRENT_LIST_DIR})  
include(${DIR_OF_CSPOT_CMAKE}/Other.cmake)

add_library(mio INTERFACE IMPORTED)
set_target_properties(mio PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${DEP}/mio"
    INTERFACE_LINK_LIBRARIES "${DEP}/mio/mio.o;${DEP}/mio/mymalloc.o"
)

add_library(woof INTERFACE IMPORTED)
set_target_properties(woof PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${WOOFC}"
    INTERFACE_LINK_LIBRARIES "${WOOFC}/woofc.o;${WOOFC}/woofc-access.o;${WOOFC}/woofc-cache.o"
)

add_library(woof_host INTERFACE IMPORTED)
set_target_properties(woof_host PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${WOOFC}"
    INTERFACE_LINK_LIBRARIES "${WOOFC}/woofc-host.o"
)

add_library(woof_thread INTERFACE IMPORTED)
set_target_properties(woof_thread PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${WOOFC}"
    INTERFACE_LINK_LIBRARIES "${WOOFC}/woofc-thread.o"
)

add_library(woof_log INTERFACE IMPORTED)
set_target_properties(woof_log PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${WOOFC}"
    INTERFACE_LINK_LIBRARIES "${WOOFC}/log.o;${WOOFC}/host.o;${WOOFC}/event.o"
)

add_library(cwpack INTERFACE IMPORTED)
set_target_properties(cwpack PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${WOOFC}/cwpack"
    INTERFACE_LINK_LIBRARIES "${WOOFC}/cwpack/cwpack.o"
)

add_library(woof_mpack INTERFACE IMPORTED)
set_target_properties(woof_mpack PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${WOOFC}"
    INTERFACE_LINK_LIBRARIES "${WOOFC}/msgpack-ep.o;cwpack"
)

add_library(cspot INTERFACE IMPORTED)
set_target_properties(cspot PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${WOOFC}"
    INTERFACE_LINK_LIBRARIES "mio;woof;woof_log;woof_host;woof_mpack;pthread;m;czmq;euca_utils;${WOOFC}/uriparser2/liburiparser2.a;${WOOFC}/lsema.o"
)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/cspot/)

function(cspot_add_handler handler name)
    add_executable(${handler}_fun "${WOOFC}/woofc-shepherd.c")
    target_link_libraries(${handler}_fun PUBLIC cspot)
    target_link_libraries(${handler}_fun PUBLIC ${handler})
    target_compile_definitions(${handler}_fun PUBLIC "WOOF_HANDLER_NAME=${name}")

    add_custom_command(TARGET ${handler}_fun POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${handler}_fun> ${CMAKE_BINARY_DIR}/cspot/
        COMMAND ${CMAKE_COMMAND} -E copy ${WOOFC}/woofc-container ${CMAKE_BINARY_DIR}/cspot/
        COMMAND ${CMAKE_COMMAND} -E copy ${WOOFC}/woofc-namespace-platform ${CMAKE_BINARY_DIR}/cspot/
    )
endfunction()
