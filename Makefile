#Declared Variables

CC = g++
LANG_STD = -std=c++17
COMPLIER_FLAGS = -Wall -Wfatal-errors
INCLUDE_PATH = -I"./libs/"
SRC_FILES = ./src*.cpp ./src/Game/*.cpp ./src/Logger/*.cpp
LINKER_FLAGS = -lSDL2 -llua5.3 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
OBJ_NAME = gameengine

#Declare Makefile rules

build:
	$(CC) $(COMPLIER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) $(LINKER_FLAGS) -o $(OBJ_NAME)

run:
	./$(OBJ_NAME)

clean:
	rm $(OBJ_NAME)
