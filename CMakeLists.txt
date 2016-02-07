cmake_minimum_required(VERSION 3.1)

project(libgif C)

if(MSVC)
    set(CMAKE_DEBUG_POSTFIX "d")
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
    add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)
endif()

set(GIFLIB_SRC
lib/dgif_lib.c
lib/egif_lib.c
lib/gif_err.c
lib/gif_font.c
lib/gif_hash.c
lib/gif_lib.h
lib/gif_lib_private.h
lib/gifalloc.c
lib/openbsd-reallocarray.c
lib/quantize.c)

add_library(libgif SHARED ${GIFLIB_SRC})
add_library(libgif_static STATIC ${GIFLIB_SRC})

set_target_properties(libgif_static PROPERTIES 
COMPILE_PDB_NAME_DEBUG "libgif_staticd"
COMPILE_PDB_NAME_RELWITHDEBINFO "libgif_static")

target_compile_definitions(libgif_static PUBLIC -DGIFLIB_STATIC)

install(TARGETS libgif libgif_static
RUNTIME DESTINATION bin
LIBRARY DESTINATION lib
ARCHIVE DESTINATION lib)

install(FILES lib/gif_lib.h DESTINATION include)
