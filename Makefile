#
CPP=g++
CPPFLAGS=-g -W -Wall -Werror -Wpedantic
EMFLAGS=-s USE_SDL=2 -s ALLOW_MEMORY_GROWTH=1
LINKLIBS=-lSDL2 -LlibFracLand -lFracLand
EMFILES=--emrun

export AR
export CPP
export CPPFLAGS

web: sdlfracland.html
	echo Done

linux: sdlfracland
	echo Done

OBJECTS=\
	LandscapeSDL.o\
	main.o

sdlfracland.html: CPP=em++
sdlfracland.html: AR=emar
sdlfracland.html: CPPFLAGS+=$(EMFLAGS)
sdlfracland.html: libFracLand/libFracLand.a $(OBJECTS)
	$(CPP) $(CPPFLAGS) $(OBJECTS) -o $@ $(LINKLIBS) $(EMFILES)

sdlfracland: libFracLand/libFracLand.a $(OBJECTS)
	$(CPP) $(CPPFLAGS) $(OBJECTS) -o $@ $(LINKLIBS)

libFracLand/libFracLand.a: libFracLand/*.h libFracLand/*.cpp libFracLand/Makefile
	$(MAKE) -C libFracLand

clean:
	rm -f *.o *~ sdlfracland sdlfracland.html sdlfracland.wasm sdlfracland.data sdlfracland.js
	$(MAKE) -C libFracLand clean

.SUFFIXES: .cpp .o

.cpp.o:
	$(CPP) $(CPPFLAGS) -c $<

