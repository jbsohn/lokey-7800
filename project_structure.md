# 🧱 Project Structure – LOKEY

> This document describes the organization of the LOKEY project. LOKEY is a modular, RP2040-based audio system designed for use with Atari 7800 cartridges, capable of emulating POKEY and playing tracker-based music (e.g., XM modules).

---

## 📁 Directory Layout

```
lokey/
├── CMakeLists.txt                # Top-level CMake config
│
├── include/                     # Shared public headers
│   └── lokey_audio.h
│
├── src/                         # Core LOKEY audio engine and wrappers
│   ├── CMakeLists.txt
│   ├── ymfm_2151.hpp
│   └── ymfm_2151.cpp
│
├── firmware/                    # RP2040 firmware target
│   ├── CMakeLists.txt
│   └── main.cpp
│
├── host_test/                   # SDL2-based desktop test harness
│   ├── CMakeLists.txt
│   ├── main.cpp
│   └── sdl_audio_output.cpp
│
├── libs/                        # Vendored third-party libraries
│   ├── CMakeLists.txt
│   ├── libxm/                   # FastTracker II (XM) playback engine
│   │   └── CMakeLists.txt
│   └── atari800_pokey/          # Atari800's pokey.c/.h
│       ├── CMakeLists.txt
│       ├── pokey.c
│       └── pokey.h
```

---

## 📦 Subproject Overview

| Directory         | Purpose                                      |
|------------------|----------------------------------------------|
| `include/`        | Public headers used across targets          |
| `src/`            | Core C++ logic (wrapper for libxm, pokey)   |
| `firmware/`       | RP2040 main loop, uses `lokey_audio`        |
| `host_test/`      | Desktop SDL app to test sound engines       |
| `libs/`           | External code (vendored for now)            |
| `libxm/`          | Optional XM engine (can use FetchContent)   |
| `atari800_pokey/` | Unmodified `pokey.c/h` from Atari800        |

---

## 🔧 Build Targets

| Target Name       | Type        | Purpose                               |
|------------------|-------------|----------------------------------------|
| `lokeyaudio`     | Static Lib  | Core audio logic, used by all builds   |
| `rp2040_main`    | Executable  | Firmware entry point                   |
| `host_test`      | Executable  | SDL2 desktop test app                  |
| `pokey`          | Static Lib  | Legacy POKEY chip emulation            |
| `xm`             | Static Lib  | (Future) XM module playback engine     |

---

## ⚙️ Build System Notes

- **CMake** is used as the primary build system
- Modular structure with one `CMakeLists.txt` per subdirectory
- Compatible with:
    - Make, Ninja, Visual Studio, Xcode
    - Raspberry Pi Pico SDK (for RP2040 builds)
    - SDL2 for host test builds
- Third-party libraries are vendored in `libs/` for now; may migrate to `FetchContent` later

---

## 🛠️ Suggested Improvements

- Add `tools/` directory for asset conversion and XM file handling
- Add `hardware/` directory for KiCad schematics and BOM
- Add `tests/` for unit tests or host audio validation
- Add `.clang-format` and stricter `CMAKE_CXX_FLAGS` for consistency

---

## 📎 See Also

- [`README.md`](../README.md) – Project intro and usage
- [SDL2](https://libsdl.org/)
- [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk)
- [Atari800 Pokey Emulation](https://github.com/atari800/atari800)