# 3.9.2 is minimum required if we want to use all options of Hunter 
cmake_minimum_required(VERSION 3.10)

# option(HUNTER_ENABLED "Enable Hunter package manager" YES)
include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.25.3.tar.gz"
    SHA1 "0dfbc2cb5c4cf7e83533733bdfd2125ff96680cb"
)
project(gamewave_core VERSION 0.0.1)
enable_language(C CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
#   message("gcc detected")
#   add_compile_options("-Werror=implicit-function-declaration")
# elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
# endif()

add_subdirectory(src)
# add_subdirectory(tests)
