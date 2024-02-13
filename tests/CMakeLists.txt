# Google Test and Google Mock external project
# ref: http://www.kaizou.org/2014/11/gtest-cmake/

# We need thread support
find_package(Threads REQUIRED)
hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

include_directories(. ../src)

set(GTEST_SOURCE diz_manager_test.cpp)

add_executable(tests test_runner.cpp ${GTEST_SOURCE})


if (MSVC)
	set(LIBRETRO_SRC gamewave_libretro_static)
else()
	set(LIBRETRO_SRC gamewave_libretro)
endif()

target_link_libraries(tests ${LIBRETRO_SRC})
# target_link_libraries(tests GTest::gtest_main)
# should link both gtest and gmock
target_link_libraries(tests GTest::gmock_main)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_link_libraries(tests ${LIBCXX_LIBRARY})
endif()
message("I'm in " ${CMAKE_CURRENT_SOURCE_DIR})

gtest_discover_tests(tests WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS tests DESTINATION bin)

# enable coverage
if ("${COVERAGE}" STREQUAL "1")
    include("${CMAKE_SOURCE_DIR}/cmake/CodeCoverage.cmake")
    APPEND_COVERAGE_COMPILER_FLAGS()
    set(COVERAGE_LCOV_EXCLUDES 'tests/*' 'gmock/*' 'gtest/*' '/usr/*')
    SETUP_TARGET_FOR_COVERAGE_LCOV(
            NAME coverage
            EXECUTABLE tests
            DEPENDENCIES tests
    )
endif()
