# noxayyyy standard makefile

CC=clang++

BINARY=bin
CODEDIRS=.
INCDIRS=. ./include
LIBPATH=

DEPFLAGS=-MP -MD
CFLAGS=-Wall -g $(foreach D,$(INCDIRS),-I$(D)) $(DEPFLAGS)
LINKERFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf

CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.cpp))
OBJECTS=$(patsubst %.cpp,%.o,$(CFILES))
DEPFILES=$(patsubst %.cpp,%.d,$(CFILES))

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -v -o $@ $^ $(LIBPATH) $(LINKERFLAGS)

%.o:%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

# % is a make wildcard (% can be anything)
# @ is a special character which refers to the target
# ^ is a special character which refers to all dependencies
# < is a special character which refers to the first dependency

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES)

-include $(DEPFILES)
