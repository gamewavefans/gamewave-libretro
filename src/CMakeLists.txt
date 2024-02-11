# include_directories(.)
find_package(Threads REQUIRED)

set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/link.T")

add_library(gamewave_libretro SHARED
    libretro.cpp
    gamewave.cpp
    diz_manager.cpp
)

set_target_properties(gamewave_libretro PROPERTIES PREFIX "")
set(CMAKE_EXE_LINKER_FLAGS "-T ${LINKER_SCRIPT}")

set_source_files_properties(
  libretro/libretro.cpp
  PROPERTIES OBJECT_DEPENDS ${LINKER_SCRIPT}
)


# zlua target builds custom lua version
add_custom_target(
    zlua
    COMMAND make
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/deps/lua_gamewave
)
add_dependencies(gamewave_libretro zlua)

target_link_libraries(gamewave_libretro PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/deps/lua_gamewave/lib/liblua.a  ${CMAKE_CURRENT_SOURCE_DIR}/deps/lua_gamewave/lib/liblualib.a)
message("${CMAKE_CURRENT_SOURCE_DIR}")
# set the same type for numbers as expected
target_compile_definitions(gamewave_libretro PRIVATE LUA_NUMBER=int)

# clean-zlua target cleans zlua build artifacts
add_custom_target(clean-zlua
    COMMAND cmake --build "${CMAKE_CURRENT_BINARY_DIR}" --target clean
    COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/deps/lua_gamewave && make clean
)

hunter_add_package(ZLIB)
find_package(ZLIB CONFIG REQUIRED)
target_link_libraries(gamewave_libretro PRIVATE ZLIB::ZLIB)



hunter_add_package(ffmpeg)
find_package(ffmpeg CONFIG REQUIRED)
target_link_libraries(
    gamewave_libretro
    PUBLIC
    Threads::Threads
    ffmpeg::avcodec
    ffmpeg::avformat
    ffmpeg::avutil
    ffmpeg::swresample
    ffmpeg::swscale
)


# hunter_add_package(libyuv)
# find_package(libyuv CONFIG REQUIRED)
# target_link_libraries(gamewave_libretro PUBLIC libyuv::yuv)
