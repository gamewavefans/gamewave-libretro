project(
  'gamewave-libretro',
  'cpp',
  version: '0.0.1',
  default_options: ['warning_level=3', 'cpp_std=c++20'],
)
# lib_versions = meson.project_version().split('.')

# subdir('docs')

lua_gamewave_proj = subproject('lua_gamewave')
lua_gamewave = lua_gamewave_proj.get_variable('lua_dep')
dep_gamewave_libretro = include_directories('src')
dep_libretro_common = include_directories('deps/libretro-common')
gamewave_libretro = library(
  'gamewave_libretro',
  'src/libretro.cpp',
  'src/gamewave.cpp',
  'src/diz_manager.cpp',
  include_directories: [dep_gamewave_libretro, dep_libretro_common],
  version: meson.project_version(),
  soversion: meson.project_version(),
  dependencies: [lua_gamewave],
)

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')
gmock_dep = gtest_proj.get_variable('gmock_dep')


dep_tests = include_directories('tests')
test_exe = executable(
  'gamewave_libretro_test',
  'tests/test_runner.cpp',
  'tests/diz_manager_test.cpp',
  link_with: gamewave_libretro,
  dependencies: [gtest_dep, gmock_dep],
  include_directories: [dep_tests, dep_gamewave_libretro],
)
test('gamewave_libretro', test_exe)

