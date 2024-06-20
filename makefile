# Pacman Makefile

CC=clang++

BINARY=bin
CODEDIRS=.
INCDIRS=. ./include/ 
# $(HOME)/mingw_dep/include/SDL2/ 
LIBPATH=
# -L$(HOME)/mingw_dep/lib/

DEPFLAGS=-MP -MD
CFLAGS=-Wall -g $(foreach D,$(INCDIRS),-I$(D)) $(DEPFLAGS)
LINKERFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf

CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.cpp))
OBJECTS=$(patsubst %.cpp,%.o,$(CFILES))
DEPFILES=$(patsubst %.cpp,%.d,$(CFILES))

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $(LIBPATH) -o $@ $^ $(LINKERFLAGS)

# % is a make wildcard (% can be anything)
%.o:%.cpp
	$(CC) $(CFLAGS) -c -o $@ $< 
# @ is a special character which refers to the target
# ^ is a special character which refers to the dependency

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES)

-include $(DEPFILES)
