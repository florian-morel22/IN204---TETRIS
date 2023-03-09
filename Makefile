# include à modifier selon sa configuration
#include make_msys.inc 
#include make_linux.inc
include make_osx.inc

CXX = g++

SRC_DIR =./src
INC_DIR = ./inc
BUILD_DIR = ./build

EXEC = TETRIS
SRC = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/types_block/*.cpp)
OBJ = $(SRC:.cpp=.o)

$(EXEC): $(OBJ)
	@$(CXX) $^ -o $@ $(LIB_SFML)

Objdoss/%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -o $@ -c $<
	@echo compiling $<

.PHONY: clean
clean:
	rm src/*.o
	rm src/types_block/*.o

.PHONY: mrproper
mrproper: clean
	rm -f TETRIS

.depend:
	@makedepend -f- -- $(SRC) > .depend

  
include .depend
