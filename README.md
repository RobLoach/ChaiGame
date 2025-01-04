# ChaiLove :heart:

[![Tests](https://github.com/libretro/libretro-chailove/actions/workflows/build.yml/badge.svg)](https://github.com/libretro/libretro-chailove/actions/workflows/build.yml)
[![platform libretro](https://img.shields.io/badge/platform-libretro-brightgreen.svg)](http://buildbot.fiveforty.net/admin/buildbot/build/?name=chailove)
[![Documentation](https://img.shields.io/badge/docs-doxygen-blue.svg)](https://rawgit.com/libretro/libretro-chailove/docs/)

ChaiLove is an awesome framework you can use to make 2D games in [ChaiScript](http://chaiscript.com/). It's free, open-source, and works on Windows, Mac OS X, Linux, Android, and ARM through [libretro](https://www.libretro.com)/[RetroArch](http://retroarch.com).

[![Floppy Bird Gameplay](docs/screenshot.png)](https://www.youtube.com/watch?v=RLVwTh6qDFI&hd=1)

## Gallery

- [Floppy Bird](https://github.com/RobLoach/ChaiLove-FloppyBird)
- [Nyan Cat](https://github.com/RobLoach/ChaiLove-NyanCat)
- [Snake](examples/snake/Snake.chai)
- [Game of Life](https://github.com/RobLoach/ChaiLove-GameOfLife)
- [... and more](https://github.com/topics/chailove)

## Installation

ChaiLove is a [libretro](https://www.libretro.com/) core, which can be installed through [RetroArch](http://retroarch.com/).

1. Run [RetroArch](http://retroarch.com/)
2. *Online Updater* → *Core Updator* → *ChaiLove*

## Usage

[Floppy Bird](https://github.com/RobLoach/ChaiLove-FloppyBird) is a [free game you can download and play](https://www.youtube.com/watch?v=RLVwTh6qDFI)...

1. Run [RetroArch](http://retroarch.com/)
2. *Online Updater* → *Content Downloader* → *ChaiLove* → *FloppyBird.chailove*
3. *Load Content* → *Downloads* → *FloppyBird.chailove*

Alternatively, you can run the ChaiLove core through RetroArch via the command line:

``` bash
curl -o FloppyBird.chailove https://github.com/RobLoach/ChaiLove-FloppyBird/releases/download/1.0.1/FloppyBird.chailove
retroarch -L chailove_libretro.so FloppyBird.chailove
```

## API

The [ChaiLove API](https://raw.githack.com/libretro/libretro-chailove/docs/index.html) is roughly inspired by the [LÖVE API](https://love2d.org/wiki/Main_Page). The following `main.chai` is a [simple Hello World example](examples/simple/main.chai):

``` lua
global logo
global x = 10.0f

def load() {
	logo = love.graphics.newImage("logo.png")
}

def draw() {
	love.graphics.print("Hello World!", 400, 300)
	love.graphics.draw(logo, x, 100)
}

def update(dt) {
	x = x + 20.0f * dt
}
```

To run it, execute the following:

``` bash
retroarch -L chailove_libretro.so main.chai
```

See the [ChaiLove API](https://raw.githack.com/libretro/libretro-chailove/docs/index.html) for coverage of all the callbacks and methods in ChaiLove.

## Development

The following are some notes about the development process behind ChaiLove.

### Compiling

ChaiLove requires a C++14 compiler, and has been tested with `g++>=5.2`. To compile it, run:

```
git submodule update --init
make
```

### Testing

The automated tests can be run with:

```
make test
```

Run the testing suite through RetroArch with:

```
retroarch -L chailove_libretro.so test/main.chai
```

### Documentation

See the [ChaiLove API documentation](https://raw.githack.com/libretro/libretro-chailove/docs/index.html). Build it through [Doxygen](http://www.stack.nl/~dimitri/doxygen/) by using:

```
make docs
```

## Contributors

The following individuals contributed to ChaiLove in some way:

- [@RobLoach](http://github.com/robloach)
- [@phcoder](https://github.com/phcoder) for the many builtbot fixes
- [@webgeek1234](http://github.com/webgeek1234) for the Android support
- [@r-type](https://github.com/r-type) for [sdl-libretro](https://github.com/r-type/sdl-libretro)
- [@mudlord](https://github.com/mudlord) for the [libretro-common](https://github.com/libretro/libretro-common) audio system
- [@orbea](http://github.com/orbea)
- [@fetzerch](http://github.com/fetzerch)
- [@bparker06](https://github.com/bparker06)
- [@twinaphex](http://github.com/twinaphex)
- [@ToKe79](https://github.com/ToKe79)
- [@konsumer](https://github.com/konsumer)
- [@baxysquare](https://github.com/baxysquare) for the [Logo](docs/chailove.png)

And many others!

## License

[MIT](COPYING)
