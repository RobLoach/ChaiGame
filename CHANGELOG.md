# Changelog
All notable changes to [ChaiLove](https://github.com/RobLoach/ChaiLove) will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

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
