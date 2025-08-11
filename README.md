# Gamewave libretro core

New libretro core loosely based on [Vectrexia](https://github.com/beardypig/vectrexia-emulator).

## Compilation

To compile this `libretro` core use `meson`. Your C++ compiler must support the C++23 standard.

```shell
meson setup build # add "-Dbuildtype=debug" for a debug build
meson compile -C build
```

## Running core

```bash
flatpak run --branch=stable --arch=x86_64 --command=retroarch org.libretro.RetroArch -L /home/halamix2/repos/reverse/gamewave/gamewave-libretro/build/gamewave_libretro.so "/home/halamix2/repos/reverse/gamewave/games/Click! (USA)/gamewave.diz"
```

Native;

```bash
retroarch -L /home/halamix2/repos/reverse/gamewave/gamewave-libretro/build/gamewave_libretro.so "/home/halamix2/repos/reverse/gamewave/games/Click! (USA)/gamewave.diz"
```

## Debug

```bash
flatpak run --command=sh --devel org.libretro.RetroArch
gdb -ex=run -args /app/bin/retroarch -L /home/halamix2/repos/reverse/gamewave/gamewave-libretro/build/gamewave_libretro.so "/home/halamix2/repos/reverse/gamewave/games/Click! (USA)/gamewave.diz"
```

## Unit tests

```bash
meson setup build # add "-Dbuildtype=debug" for a debug build
meson test -C build
```

## What's working

- loading .diz files
- lua libraries
  - bit
  - zmath

## What's not working

- everything
- lua libraries
  - all of them
  - engine
  - gl
  - iframe
  - log
  - rm - 50% - missing `LoadFile` / `UnloadFile`
  - time - 50% - issue with `sleep()`
- font
- video
- audio
- graphics
- input
- saves

## Dependencies:

- libretro (included with git submodule)
- libpthread
- Lua 5.0.2, [with Gamewave-specific changes](https://github.com/gamewavefans/lua_gamewave)
- zlib
- ffmpeg
<!-- - libyuv - included by Hunter -->

## Possible future deps

- SDL2
- libcdio

## Flatpak integration

To use the core in the flatpak version of theretroarch:

- link the .so file to `.var/app/org.libretro.RetroArch/config/retroarch/cores/`
- link the .info file to `/var/lib/flatpak/app/org.libretro.RetroArch/current/active/files/share/libretro/info/`
