cmake_minimum_required(VERSION 3.20)
project(minicore_mpeg3)
enable_language(C CXX)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LINKER_SCRIPT "/home/halamix2/repos/reverse/gamewave/gamewave-libretro/link.T")

add_library(minicore_mpeg3 SHARED
    # /usr/include/mpeg3/libmpeg3.h
    # /usr/include/mpeg3/mpeg3private.h
    # /usr/include/mpeg3/mpeg3protos.h
    libretro.cpp
)

set_target_properties(minicore_mpeg3 PROPERTIES PREFIX "")
set(CMAKE_EXE_LINKER_FLAGS "-T ${LINKER_SCRIPT}")

set_source_files_properties(libretro/libretro.cpp
        PROPERTIES OBJECT_DEPENDS ${LINKER_SCRIPT})

add_library( mpeg3 SHARED IMPORTED )
# You can define two import-locations: one for debug and one for release.
set_target_properties( mpeg3 PROPERTIES IMPORTED_LOCATION /usr/lib64/libmpeg3.so.1 )
find_library(mpee mpeg3)
target_link_libraries(minicore_mpeg3 mpeg3)
# find_package(ZLIB)
# target_link_libraries(gamewave_libretro ZLIB::ZLIB)
