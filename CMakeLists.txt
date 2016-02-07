cmake_minimum_required(VERSION 2.8)

project(libgif C)

set(INSTALL_BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin" CACHE PATH "Installation directory for executables")
set(INSTALL_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib" CACHE PATH "Installation directory for libraries")
set(INSTALL_INC_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "Installation directory for headers")
set(INSTALL_MAN_DIR "${CMAKE_INSTALL_PREFIX}/share/man" CACHE PATH "Installation directory for manual pages")
set(INSTALL_PKGCONFIG_DIR "${CMAKE_INSTALL_PREFIX}/share/pkgconfig" CACHE PATH "Installation directory for pkgconfig (.pc) files")

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
lib/quantize.c)

add_library(libgif SHARED ${GIFLIB_SRC})
add_library(libgif_static STATIC ${GIFLIB_SRC})

target_compile_definitions(libgif_static PUBLIC -DGIFLIB_STATIC)

install(TARGETS libgif libgif_static
RUNTIME DESTINATION bin
LIBRARY DESTINATION lib
ARCHIVE DESTINATION lib)

install(FILES lib/gif_lib.h DESTINATION ${INSTALL_INC_DIR})
