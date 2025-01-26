# Changelog
All notable changes to [ChaiLove](https://github.com/RobLoach/ChaiLove) will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## 2.0.0 - WIP
### Changed
- Moved from [sdl-libretro](https://github.com/libretro/sdl-libretro) to [pntr](https://github.com/robloach/pntr) and [pntr_app](https://github.com/robloach/pntr)

## 1.3.0 - 2024-05-11
### Fixes
- Fix playing empty ogg files through `libretro-common`, by @phcoder
- docs: Remove the dev branch by @RobLoach in https://github.com/libretro/libretro-chailove/pull/410
- Enable compilation for psvita and switch by @phcoder in https://github.com/libretro/libretro-chailove/pull/417
- Update mixer to thread-safe version by @phcoder in https://github.com/libretro/libretro-chailove/pull/416
- Switch straight file I/O to VFS by @phcoder in https://github.com/libretro/libretro-chailove/pull/415
- love: Fix buffer overflow by @phcoder in https://github.com/libretro/libretro-chailove/pull/419
- Misc build fixes by @phcoder in https://github.com/libretro/libretro-chailove/pull/418
- Fix `unix-armv7-hardfloat-neon` build by @zoltanvb in https://github.com/libretro/libretro-chailove/pull/420
- Move from std::cout to libretro logging by @phcoder in https://github.com/libretro/libretro-chailove/pull/412
- Update GitHub Actions by @RobLoach in https://github.com/libretro/libretro-chailove/pull/427

### Changed
- `love.filesystem.remove()` has been removed
- SDL_tty: Update by @gouchi in https://github.com/libretro/libretro-chailove/pull/426
- Update libretro-common by @RobLoach in https://github.com/libretro/libretro-chailove/pull/413

## 1.2.1 - 2022-03-07
### Fixes
- Update `libretro-common` for audio fixes
- Fix miyoo compilation name by @phcoder in https://github.com/libretro/libretro-chailove/pull/408
- Fix osx-arm64 compilation and few Makefile cleanups by @phcoder in https://github.com/libretro/libretro-chailove/pull/409

## 1.2.0 - 2022-02-20
### Fixes
- Make PhysFS only support `.zip` compression

### Chores
- Update vendor dependencies
- Enable compilation of dingus, ios-arm64 and tvos-arm64 (by phcoder)
- Remove submodule manipulation from `Makefile`
- Switched Travis testing for [GitHub Actions](https://github.com/libretro/libretro-chailove/actions)

## 1.1.0 - 2019-12-31
### Fixes
- iOS compilation
  - By [@jet082](https://github.com/jet082) in [#383](https://github.com/libretro/libretro-chailove/pull/383)
- Updated dependencies

## 1.0.0 - 2019-08-23
### Chores
- Updated dependencies
- Removed semantic version checking for platform compatibility

## 0.32.0 - 2019-03-10
### Features
- [BunnyMark](examples/bunnymark) to test performance

### Chores
- ChaiLove now requires content to run
- Updated ChaiScript_Extras for more string methods
- Updated PhysFS
- Updated libretro-common
- Updated random to fix a gcc 7.3+ error
- Updated stb

## 0.31.0 - 2018-12-24
### Chores
- Update to use the libretro audio callback
- Updated cppcodec
- Updated PhysFS
- Updated libretro-common

## 0.30.0 - 2018-11-14
### Features
- Added support for classic_armv7_a7
  - By [@classicmods](https://github.com/classicmods) and [@swingflip](https://github.com/swingflip)
- Added `lib/init.chai` loading with `require("lib")`
- Updated ChaiScript/ChaiScript_Extras
- Updated libretro/libretro-common

## 0.29.1 - 2018-11-05
### Chores
- Moved String Methods to [ChaiScript_Extras](https://github.com/ChaiScript/ChaiScript_Extras)
- Replaced use of `filesystem/path.h` with internal functions
- Updated ChaiScript/ChaiScript_Extras
- Updated libretro/libretro-common
- Updated effolkronium/random

## 0.29.0 - 2018-10-13
### Fixes
- Fixed `/libretro/saves` mounting

### Features
- Added `string::trim()`
- Added `string::split()`
- Adds loading of `conf.chai` for the `conf()` callback

## 0.28.0 - 2018-10-07
### Features
- `love.timer.step()` now returns `dt`
- Adds `string::replace(search, replace)` to replace all instances of a string

### Fixes
- Fixes undefined reference to `process_sinc_neon_asm()`
  - [#322](https://github.com/libretro/libretro-chailove/issues/322) found by [@ToKe79](https://github.com/ToKe79)
- Fixes `love.graphics.draw(image)` with no x and y parameter

### Chores
- Update libretro-common
- Update PhysFS
- Rework the testing framework
- Fix Doxygen warnings

## 0.27.0 - 2018-09-25
### Features
- Live updating of core options
- Mounts `/libretro/core` as the directory where the core was loaded from
- Adds `love.filesystem.getSaveDirectory()`
- Adds `love.filesystem.newFileData(contents, name)`
- Adds `love.filesystem.getExecutablePath()`
- Adds `love.filesystem.remove()`

### Fixes
- Fixed loading ChaiLove without active content

## 0.26.1 - 2018-09-19
### Fixes
- Fixed `mount()` with relative paths
- Fixed mounting of saves and system directories
- Fix for compiling `nearest_resampler.c` without `STATIC_LINKING` ([#312](https://github.com/libretro/libretro-chailove/pull/312))
  - By [@twinaphex](https://github.com/twinaphex)
- Fix rewind by removing compression of save states

## 0.26.0 - 2018-09-13
### Features
- Added a global `require()` function to load modules ([#308](https://github.com/libretro/libretro-chailove/pull/308))
- Added OEM-102 key support (sometimes `\` on EUR keyboard) ([#309](https://github.com/libretro/libretro-chailove/pull/309))

## 0.25.1 - 2018-09-11
### Fixes
- Fix Windows build
- Fix Android build ([#305](https://github.com/libretro/libretro-chailove/issues/305))
  - By [@bparker06](https://github.com/bparker06)

## 0.25.0 - 2018-09-08
### Features
- Added Cheat support
  - `cheatset(index, enabled, code)`
  - `cheatreset()`
- Added `.ogg` audio support

### Fixes
- Fixed save state loading
- Fixed `love.filesystem.mount()` logic

## 0.24.0 - 2018-09-03
### Features
- Update to use libretro-common audio
- Added `love.filesystem.newFileData()`
- Added `love.system.getClipboardText()`
- Added `love.system.setClipboardText()`
- Added `love.data.encode()`
- Added `love.data.decode()`

### Chores
- Added `love.filesystem.mount()` test
- Updated documentation
- Updated unit testing framework
- Additional method chaining functions

## 0.23.1 - 2018-08-28
### Fixes
- Clean up of git submodules

## 0.23.0 - 2018-08-27
### Chores
- Updated dependencies
  - [ChaiScript 6.1.0](https://github.com/ChaiScript/ChaiScript/releases/tag/v6.1.0)
  - PhysFS
  - libretro-common
  - libretro-deps
  - noarch
  - styleguide

### Fixes
- Fix uninitalized image pointer causing segfault
  - By [@orbea](https://github.com/orbea) in [#263](https://github.com/libretro/libretro-chailove/pull/263)

## 0.22.2 - 2018-05-06
### Fixes
- Documentation

## 0.22.1 - 2018-05-06
### Fixes
- Removed `Http()` due to cross-platform incompatibility

## 0.22.0 - 2018-05-06
### Features
- `love.filesystem.createDirectory()` to make directories
- `love.filesystem.write()` to write a file in the save directory

### Fixes
- Fix debug build due to undefined "z_error" and "z_verbose" in zlib
  - By [@fetzerch](https://github.com/fetzerch) in [#256](https://github.com/libretro/libretro-chailove/pull/256)

## 0.21.0 - 2018-05-02
### Chores
- Switched to [libretro-deps](https://github.com/libretro/libretro-deps) for freetype and zlib
- Clean up of image and audio memory allocation
- Updated documentation

### Features
- `love.system.execute()` to execute a operating system shell command
- `love.audio.newSource()` now has an optional `type` parameter
- `love.joystick` comes with a cleaner API
- `exit()` callback, which is called when is quitting the game
- `love.filesystem` now mounts `libretro/assets`, `libretro/system` and `libretro/saves`

## 0.20.1 - 2018-04-24
### Bug Fixes
- Better memory usage
- Compilation warnings

## 0.20.0 - 2018-04-22
### Features
- No Game demo when ChaiLove is loaded without content
- Version mismatch warning when content's ChaiLove version doesn't match core's
- `love.data.hash()` `sha1` support
- `love.system.getUsername()`

## 0.19.0 - 2018-04-13
### Features
- Android build
  - By [@webgeek1234](https://github.com/webgeek1234)
- `love.data.hash()` to retrieve MD5 hashes from content
- Windows automated testing with [Appveyor](https://ci.appveyor.com/project/RobLoach/libretro-chailove)

## 0.18.1 - 2018-04-09
### Chores
- Documentation

## 0.18.0 - 2018-04-03
### Features
- [Semantic Versioning](https://semver.org/) checks
  - Use `t.version = "0.18.0"` in `conf(t)` to specify which ChaiLove version you're targeting
- `love.graphics.getDimensions()`
- `love.filesystem.getInfo()`
- `love.filesystem.isSymlink()`

### Breaking Changes
- `love.math.compress()` is now `love.data.compress()`
- Documentation

## 0.17.0 - 2018-03-18
### Added
- `love.system.getOS()` now returns actual operating system name
- `love.console` an in-game console toggled with the tilde key
  - Enable the console with `love.console.setEnabled(true)`
- `love.graphics.getColor()` to retrieve the active painting color
- `love.window.showMessageBox()` to display on-screen messages

### Fixed
- Cleaned the Makefile dependency chain

## 0.16.1 - 2018-03-12
### Added
- `List()` for linked list

## 0.16.0 - 2018-03-05
### Fixed
- Fix undefined zlib symbols in debug build
  - By [@fetzerch](https://github.com/fetzerch) in [#200](https://github.com/libretro/libretro-chailove/pull/200)

### Changed
- Added `love.graphics.draw(Image)` and `love.graphics.draw(Image, Quad)` with default position of 0,0
- Update documentation

## 0.15.1 - 2017-03-05
### Changed
- Update dependencies
- Updated dependency chain in Makefile to be safe

## 0.15.0 - 2017-03-04
### Changed
- Updated the input description names
- Switch Keyboard/Mouse input from SDL API to libretro API
- `love.mousepressed()` and `love.mousereleased()` now pass the button name rather than its index

### Added
- `love.keyboard.isScancodeDown()`
- `love.mouse` `x1` and `x2` buttons

## 0.14.2 - 2018-02-17
### Changed
- Moved source to libretro organization:
  - http://github.com/libretro/libretro-chailove
- Updated documentation
- Updated dependencies
- Fixed native test

## 0.14.0 - 2018-01-16
### Changed
- Removed global objects, use `love` namespace instead
  - Before: `graphics.draw()`
  - After: `love.graphics.draw()`
- Cleaned up global `love.config`

## 0.13.0 - 2017-12-20
### Added
- Documentation
- `math.random()` for int, float and double numbers

### Fixed
- Renamed `mousemove()` callback to `mousemoved()`
- `love.graphics.setDefaultFilter()` flags

## 0.12.0 - 2017-12-13
### Added
- `SoundData.getVolume()`
- `SoundData.setVolume()`

### Changed
- Updated C++ namespace from `Modules` to `love`
- [Method chaining](https://en.wikipedia.org/wiki/Method_chaining) for most functions
    ```
    graphics.love.point(100,100).point(50, 200)
    ```
- Moved `Types` namespace to `love::Types`

## 0.11.1 - 2017-12-10
### Fixed
- Version number

## 0.11.0 - 2017-12-09
### Added
- `love` namespace
  - Example: `love.graphics.draw()`
- `love.graphics.draw()` rotation and scaling
- `love.graphics.setDefaultFilter()`
- `love.graphics.getDefaultFilter()`

### Changed
- [ChaiScript_Extras](https://github.com/ChaiScript/ChaiScript_Extras) now using original source as upstream issue is fixed
- Updated [libretro-common](http://github.com/libretro/libretro-common)
- Updated [random](https://github.com/libretro/sdl-libretro)
- Updated [sdl-libretro](https://github.com/libretro/sdl-libretro)

### Fixed
- `keyreleased()` callback parameter types

## 0.10.0 - 2017-11-30
### Added
- Mac support
- Unit testing

### Changed
- Coding standards

## 0.9.0 - 2017-11-25
### Added
- Namespace update
- Documentation
