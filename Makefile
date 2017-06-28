
DEBUG = 0

ifeq ($(platform),)
	platform = unix
ifeq ($(shell uname -a),)
	platform = win
else ifneq ($(findstring Darwin,$(shell uname -a)),)
	platform = osx
else ifneq ($(findstring MINGW,$(shell uname -a)),)
	platform = win
endif
endif

TARGET_NAME := chaigame

ifeq ($(platform), unix)
	CC = gcc
	CXX = g++
	CFLAGS = -g -O2
	CXXFLAGS = -g -O2  -fno-merge-constants
	TARGET := $(TARGET_NAME)_libretro.so
	fpic := -fPIC
	SHARED := -shared -Wl,--no-undefined -Wl,--version-script=link.T
	ENDIANNESS_DEFINES := -DLSB_FIRST
	FLAGS += -D__LINUX__
	SDL_PREFIX := unix
# android arm
else ifneq (,$(findstring android,$(platform)))
	TARGET := $(TARGET_NAME)_libretro_android.so
	fpic = -fPIC
	SHARED := -lstdc++ -lstd++fs -llog -lz -shared -Wl,--version-script=link.T -Wl,--no-undefined
	CFLAGS +=  -g -O2
	CC = arm-linux-androideabi-gcc
	CXX = arm-linux-androideabi-g++
# cross Windows
else ifeq ($(platform), wincross64)
	TARGET := $(TARGET_NAME)_libretro.dll
	AR = x86_64-w64-mingw32-ar
	CC = x86_64-w64-mingw32-gcc
	CXX = x86_64-w64-mingw32-g++
	SHARED := -shared -Wl,--no-undefined -Wl,--version-script=link.T
	LDFLAGS += -static-libgcc -static-libstdc++ -lstd++fs
	ENDIANNESS_DEFINES := -DLSB_FIRST
	FLAGS +=
	EXTRA_LDF := -lwinmm -Wl,--export-all-symbols
	SDL_PREFIX := win
else
	TARGET :=  $(TARGET_NAME)_retro.dll
	CC = gcc
	CXX = g++
	SHARED := -shared -Wl,--no-undefined -Wl,--version-script=link.T
	LDFLAGS += -static-libgcc -static-libstdc++  -lstd++fs
	ENDIANNESS_DEFINES := -DLSB_FIRST
	FLAGS +=
	EXTRA_LDF = -lwinmm -Wl,--export-all-symbols
	SDL_PREFIX := win
endif

OBJECTS := libretro.o Application.o \
	chaigame/chaigame.o \
	chaigame/graphics.o \
	chaigame/keyboard.o \
	chaigame/script.o \
	chaigame/filesystem.o \
	chaigame/image.o \
	chaigame/sound.o \
	chaigame/system.o \
	chaigame/src/ImageData.o \
	chaigame/src/Image.o \
	vendor/physfs/extras/physfsrwops.o

all: vendor/physfs/libphysfs.a vendor/libretro-common/include/libretro.h $(TARGET)

ifeq ($(DEBUG), 0)
   FLAGS += -O3 -ffast-math -fomit-frame-pointer
else
   FLAGS += -O0 -g
endif

LDFLAGS +=  $(fpic) $(SHARED) \
	vendor/sdl-libretro/libSDL_gfx_$(SDL_PREFIX).a \
	vendor/sdl-libretro/SDL_image_$(SDL_PREFIX).a \
	vendor/sdl-libretro/libSDL_mixer_$(SDL_PREFIX).a \
	vendor/sdl-libretro/libSDL_$(SDL_PREFIX).a \
	vendor/physfs/libphysfs.a \
	-ldl -ljpeg -lpng \
	-lmikmod -lvorbisfile -logg \
	-lpthread $(EXTRA_LDF)
FLAGS += -I. \
	-Ivendor/sdl-libretro/include \
	-Ivendor/libretro-common/include \
	-Ivendor/chaiscript/include \
	-Ivendor/physfs/src

WARNINGS :=

ifneq ($(DISABLE_CHAISCRIPT),)
	FLAGS += -D__DISABLE_CHAISCRIPT__
endif
FLAGS += -D__LIBRETRO__ $(ENDIANNESS_DEFINES) $(WARNINGS) $(fpic)

CXXFLAGS += $(FLAGS) -fpermissive -std=c++14
CFLAGS += $(FLAGS) -std=gnu99

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(TARGET) $(OBJECTS)

vendor/libretro-common/include/libretro.h:
	git submodule init
	git submodule update

vendor/physfs/libphysfs.a: vendor/libretro-common/include/libretro.h
	cd vendor/physfs && cmake . && make C_FLAGS=-fPIC

.PHONY: clean

noscript:
	make DISABLE_CHAISCRIPT=1

test: noscript
	retroarch -L *.so
