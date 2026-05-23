CC=clang++
BINARY=bin

ENGINE_DIR=./engine
ENGINE_LIB=$(ENGINE_DIR)/libnox_engine.a

SRC_DIRS=./src
INC_DIRS=./include ./engine/include /usr/local/old-sdl2/include /usr/local/old-sdl2/include/SDL2
OBJ_DIRS=./obj

DEP_FLAGS=-MP -MMD
CFLAGS=-std=c++0x -Wall -Wextra -pedantic -g $(foreach D,$(INC_DIRS),-I$(D)) $(DEP_FLAGS)
LD_FLAGS=-L/usr/local/old-sdl2/lib -L$(ENGINE_DIR) -lnox_engine -lSDL2 -lSDL2_image

CFILES=main.cpp $(wildcard $(SRC_DIRS)/*.cpp)
OBJECTS=$(patsubst %.cpp, $(OBJ_DIRS)/%.o, $(CFILES))
DEPFILES=$(OBJECTS:.o=.d)

.PHONY: all clean $(ENGINE_LIB)

all: $(BINARY)

$(BINARY): $(ENGINE_LIB) $(OBJECTS)
	$(CC) -v -o $@ $^ $(LD_FLAGS)

$(ENGINE_LIB):
	$(MAKE) -C $(ENGINE_DIR)

$(OBJ_DIRS)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BINARY) $(OBJ_DIRS) $(DEPFILES)
	$(MAKE) -C $(ENGINE_DIR) clean

-include $(DEPFILES)
