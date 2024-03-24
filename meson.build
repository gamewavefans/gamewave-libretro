project('gamewave-libretro', 'cpp',
  version : '0.0.1',
  default_options : ['warning_level=3', 'cpp_std=c++20'])
lib_versions = meson.project_version().split('.')

# subdir('src')
# subdir('tests')
# subdir('docs')


inc_src = include_directories('src')
gamewave_libretro = shared_library('gamewave_libretro',
  'src/libretro.cpp',
  'src/gamewave.cpp',
  'src/diz_manager.cpp',
  include_directories: [inc_src],
  version: meson.project_version(),
  soversion: meson.project_version(),
)

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')
gmock_dep = gtest_proj.get_variable('gmock_dep')


inc_tests = include_directories('tests')
test_exe = executable('gamewave_libretro_test',
  'tests/test_runner.cpp',
  'tests/diz_manager_test.cpp',
  link_with : gamewave_libretro,
  dependencies: [gtest_dep, gmock_dep],
  include_directories: [inc_src, inc_tests])
test('gamewave_libretro', test_exe)
