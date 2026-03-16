CC = g++
SRC = $(wildcard src/*.cpp) 
OUT = main

INCLUDE_DIR = -Iinclude
CFLAGS = -Wall $(INCLUDE_DIR)
LDFLAGS = -lm

ifeq ($(OS),Windows_NT)
    IS_WINDOWS = 1
else
    IS_WINDOWS = 0
endif

ifeq ($(IS_WINDOWS), 1)
    OUT = main.exe
    RAYLIB_DIR = include/raylib
    CFLAGS += -I$(RAYLIB_DIR)/include
    LDFLAGS += -L$(RAYLIB_DIR)/lib -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows
else
    OUT = main
    CFLAGS += -I/usr/include/raylib
    LDFLAGS += -lraylib -lm
endif

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
ifeq ($(IS_WINDOWS), 1)
	del /Q $(OUT)
else
	rm -f $(OUT)
endif
