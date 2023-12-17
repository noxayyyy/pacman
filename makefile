# Pacman Makefile

CC=g++

BINARY=bin
CODEDIRS=.
INCDIRS=. ./include/ C:/mingw_dep/include/SDL2/ 
LIBPATH=-LC:/mingw_dep/lib/

DEPFLAGS=-MP -MD
CFLAGS=-w -g $(foreach D,$(INCDIRS),-I$(D)) $(DEPFLAGS)
LINKERFLAGS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image

CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.cpp))
OBJECTS=$(patsubst %.cpp,%.o,$(CFILES))
DEPFILES=$(patsubst %.cpp,%.d,$(CFILES))

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBPATH) -o $@ $^ $(LINKERFLAGS)

# % is a make wildcard (% can be anything)
%.o:%.cpp
	$(CC) $(CFLAGS) -c -o $@ $^ 
# @ is a special character which refers to the target
# ^ is a special character which refers to the dependency

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES)

-include $(DEPFILES)