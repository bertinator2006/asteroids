COMPILER = clang
SOURCE_LIBS = -Ilib/
OSX_OPT = -Llib/ -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a
OSX_OUT = -o "bin/build_osx"
DEBUG_OUT = -o "game"
CFILES = VSCode/*.c

osx_debug:
	$(COMPILER) $(CFILES) $(SOURCE_LIBS) $(DEBUG_OUT) $(OSX_OPT)

build_osx:
	$(COMPILER) $(CFILES) $(SOURCE_LIBS) $(OSX_OUT) $(OSX_OPT)