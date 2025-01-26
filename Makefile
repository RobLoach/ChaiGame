TARGET_NAME := chailove

ifeq ($(VERBOSE),)
Q=@
endif

include Makefile.libretro

ifeq ($(STATIC_LINKING),1)
	FLAGS += -DSTATIC_LINKING
endif

FLAGS += -D__LIBRETRO__ $(COREDEFINES) $(ENDIANNESS_DEFINES) $(PLATFORM_DEFINES) $(WARNINGS) $(fpic)

CXXFLAGS += $(FLAGS) -std=c++14
CFLAGS += $(FLAGS) -std=gnu99

# Ignore first attempt builds, and re-try for a cleaner dependency chain.
all: $(TARGET)
	$(MAKE) $(TARGET)

$(TARGET): $(OBJECTS)
ifeq ($(STATIC_LINKING), 1)
	$(AR) rcs $@ $(OBJECTS)
else
	$(CXX) -o $@ $^ $(LDFLAGS)
endif

%.o: %.cpp
	@echo CXX $<
	$(Q)$(CXX) -c -o $@ $< $(CXXFLAGS) -include retro_endianness.h

%.o: %.c
	@echo CXX $<
	$(Q)$(CC) -c -o $@ $< $(CFLAGS) -include retro_endianness.h

%.o: %.m
	$(CC) -c -o $@ $< $(CFLAGS) -include retro_endianness.h

%.o: %.S
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(TARGET) $(OBJECTS)

test: unittest unittest-chailove
	@echo "Run the testing suite by using:\n\n    retroarch -L $(TARGET) test/main.chai\n\n"

unittest: all
	@retroarch -L $(CORE_DIR)/$(TARGET) test/unittests/main.chai

unittest-chailove: all
	@retroarch -L $(CORE_DIR)/$(TARGET) test/test.chailove

examples: all
	@retroarch -L $(TARGET) examples/benchmark/main.chai

test-script: all
	@retroarch -L $(TARGET) test/main.chai

docs: docs/html

docs/html: docs-clean
	doxygen docs/Doxyfile

docs-start: docs/html
	php -S localhost:8080 -t docs/html

docs-clean:
	rm -rf docs/html

docs-deploy: docs
	npm init --force -y
	npm install push-dir
	node_modules/.bin/push-dir --dir=docs/html --branch=docs

cpplint:
	@vendor/styleguide/cpplint/cpplint.py \
		--linelength=120 \
		--quiet \
		--counting=detailed \
		--filter=-build/include,-legal/copyright,-runtime/int,-runtime-readability/braces,\
	-runtime/threadsafe_fn,-build/namespaces,-runtime/explicit,-whitespace/tab,\
	-readability/casting,-whitespace/line_length,-runtime/references \
		src/ChaiLove.cpp src/ChaiLove.h src/libretro.cpp src/love/*.h src/love/*.cpp src/love/Types/*/*.h src/love/Types/*/*.cpp

tests:
	$(MAKE) HAVE_CHAISCRIPT=0 HAVE_TESTS=1

PREFIX := /usr
INSTALLDIR := $(PREFIX)/lib/libretro
install: all
	mkdir -p $(DESTDIR)$(INSTALLDIR)
	cp $(TARGET) $(DESTDIR)$(INSTALLDIR)
