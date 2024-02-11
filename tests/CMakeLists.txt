# Google Test and Google Mock external project
# ref: http://www.kaizou.org/2014/11/gtest-cmake/

# We need thread support
find_package(Threads REQUIRED)


add_dependencies(libgmock gmock)
