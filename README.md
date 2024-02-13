# Gamewave libretro core

New libretro core loosely based on [Vectrexia](https://github.com/beardypig/vectrexia-emulator).

## Compilation

To compile this `libretro` core use `cmake`. Your C++ compiler must support the C++23 standard.

```shell
$ cmake -E make_directory build && cmake -E chdir build cmake ..
$ cmake --build build -- all test # compile and run the tests
```

# Testing core?

```bash
/usr/bin/flatpak run --branch=stable --arch=x86_64 --command=retroarch org.libretro.RetroArch -L /home/halamix2/repos/reverse/gamewave/gamewave-libretro/build/src/gamewave_libretro.so "/home/halamix2/repos/reverse/gamewave/games/Click! (USA)/gamewave.diz"
```

# Unit tests

```bash
cmake -E make_directory build
cmake --build build -- all test # compile and run the tests
```

# What's working

- nothing

# What's not working

- everything
- font
- video
- audio
- graphics
- input
- saves

# Dependencies:

- libretro (included with git submodule)
- libpthread
- Lua 5.0.2, [with Gamewave-specific changes](https://github.com/gamewavefans/lua_gamewave)
- zlib - included by Hunter
- ffmpeg - included by Hunter
<!-- - libyuv - included by Hunter -->

# Possible future deps:

- SDL2
- libcdio
