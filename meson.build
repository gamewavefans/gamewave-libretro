project(
  'gamewave-libretro',
  ['cpp', 'c'],
  version: '0.0.1',
  default_options: ['warning_level=3', 'cpp_std=c++26'],
)
# lib_versions = meson.project_version().split('.')

# subdir('docs')

dep_gamewave_libretro = include_directories('src')
dep_deps = include_directories('deps')

# zlib, Threads::Threads
# ffmpeg::avformat
# ffmpeg::avcodec
# ffmpeg::avutil
# ffmpeg::swresample
# ffmpeg::swscale
# libyuv

dependencies = [
  dependency('lua_gamewave'),
  dependency('zlib'),
  dependency('libavformat', version: '>= 57.33'),
  dependency('libavcodec', version: '>= 57.37'),
  dependency('libavutil'),
  # dependency('libswresample'),
  dependency('libswscale'),
]

# we're building both dynamic library for use in RetroArch, as well as static one to use in tests, as dynamic only exports retro_* functions
gamewave_libretro = both_libraries(
  'gamewave_libretro',
  'src/global.cpp',
  'src/libretro.cpp',
  'src/gamewave.cpp',
  'src/helpers.cpp',
  'src/iframe.cpp',
  'src/filetypes/diz.cpp',
  'src/filetypes/fimg.cpp',
  'src/filetypes/zbc.cpp',
  'src/filetypes/zbm.cpp',
  'src/filetypes/zwf.cpp',
  # 'src/zlua/audio.cpp',
  'src/zlua/bit.cpp',
  # 'src/zlua/eeprom.cpp',
  'src/zlua/engine.cpp',
  # 'src/zlua/exp_int.cpp',
  # 'src/zlua/font.cpp',
  'src/zlua/gl.cpp',
  'src/zlua/iframe.cpp',
  # 'src/zlua/input.cpp',
  'src/zlua/log.cpp',
  # 'src/zlua/movie.cpp',
  # 'src/zlua/pointer.cpp',
  'src/zlua/rm.cpp',
  # 'src/zlua/spi.cpp',
  # 'src/zlua/text.cpp',
  'src/zlua/time.cpp',
  # 'src/zlua/uart.cpp',
  # 'src/zlua/zfile.cpp',
  'src/zlua/zmath.cpp',
  include_directories: [dep_gamewave_libretro, dep_deps], #, dep_subprojects],
  version: meson.project_version(),
  soversion: meson.project_version(),
  dependencies: dependencies,
  link_args: ['-Wl,--version-script,' + meson.current_source_dir() + '/link.T'],
  # prevents library getting named libgamewave_libretro
  name_prefix: '',
)

# experiment = executable(
#   'experiment',
#   'src/helpers/filepath.cpp',
#   'experiment.cpp',
#   include_directories: [dep_gamewave_libretro, dep_deps, dep_subprojects], #, dep_ffmpeg],
# )

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')
gmock_dep = gtest_proj.get_variable('gmock_dep')

dep_tests = include_directories('tests')
test_exe = executable(
  'gamewave_libretro_test',
  'tests/test_runner.cpp',
  'tests/diz_manager_test.cpp',
  link_whole: gamewave_libretro.get_static_lib(),
  dependencies: [gtest_dep, gmock_dep],
  include_directories: [dep_tests, dep_gamewave_libretro],
)
test('gamewave_libretro', test_exe)
