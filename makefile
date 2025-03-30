# noxayyyy standard makefile

CC=clang++

BINARY=bin
STATICENGINELIB=libnox_engine.a
DYNAMICENGINELIB=libnox_engine.so

CODEDIRS=.
INCDIRS=. ./include ./engine/include

ENGINECODEDIRS=./engine
ENGINEINCDIRS=./engine/include

DEPFLAGS=-MP -MD
LINKERFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -L. -lnox_engine

CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.cpp))
OBJECTS=$(patsubst %.cpp,%.o,$(CFILES))
DEPFILES=$(patsubst %.cpp,%.d,$(CFILES))

ENGINECFILES=$(foreach D,$(ENGINECODEDIRS),$(wildcard $(D)/*.cpp))
ENGINEOBJECTS=$(patsubst %.cpp,%.o,$(ENGINECFILES))
ENGINEDEPFILES=$(patsubst %.cpp,%.d,$(ENGINECFILES))

static: enginestatic $(BINARY)

dynamic: LINKERFLAGS += -Wl,-rpath="./"
dynamic: enginedynamic $(BINARY)

enginedynamic: CFLAGS=-Wall -g $(foreach D,$(ENGINEINCDIRS),-I$(D)) -fPIC
enginedynamic: $(ENGINEOBJECTS)
	$(CC) -v -shared -o $(DYNAMICENGINELIB) $^

enginestatic: CFLAGS=-Wall -g $(foreach D, $(ENGINEINCDIRS),-I$(D)) $(DEPFLAGS)
enginestatic: $(ENGINEOBJECTS)
	ar rcs $(STATICENGINELIB) $^

$(BINARY): CFLAGS=-Wall -g $(foreach D,$(INCDIRS),-I$(D)) $(DEPFLAGS)
$(BINARY): $(OBJECTS)
	$(CC) -v -o $@ $^ $(LINKERFLAGS)

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# % is a make wildcard (% can be anything)
# @ is a special character which refers to the target
# ^ is a special character which refers to all dependencies
# < is a special character which refers to the first dependency

clean: cleanbin cleanengine

cleanbin:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES)

cleanengine:
	rm -rf $(STATICENGINELIB) $(DYNAMICENGINELIB) $(ENGINEOBJECTS) $(ENGINEDEPFILES)

-include $(DEPFILES)
-include $(ENGINEDEPFILES)
