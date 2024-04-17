# Gamewave libretro core

New libretro core loosely based on [Vectrexia](https://github.com/beardypig/vectrexia-emulator).

## Compilation

To compile this `libretro` core use `meson`. Your C++ compiler must support the C++23 standard.

```shell
meson setup build # add "-Dbuildtype=debug" for a debug build
meson compile -C build
```

# Testing core?

```bash
/usr/bin/flatpak run --branch=stable --arch=x86_64 --command=retroarch org.libretro.RetroArch -L /home/halamix2/repos/reverse/gamewave/gamewave-libretro/build/libgamewave_libretro.so "/home/halamix2/repos/reverse/gamewave/games/Click! (USA)/gamewave.diz"
```

# Unit tests

```bash
meson setup build # add "-Dbuildtype=debug" for a debug build
meson test -C build
```

# What's working

- loading .diz files

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
- zlib
- ffmpeg
<!-- - libyuv - included by Hunter -->

# Possible future deps:

- SDL2
- libcdio
