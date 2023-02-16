CXX= g++ 
CXXFLAGS= -Wall -Werror -Wfatal-errors
LIB_SFML= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -pthread

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
	rm -f *.o

.PHONY: mrproper
mrproper: clean
	rm -f TETRIS

.depend:
	@makedepend -f- -- $(SRC) > .depend

  

# Il suffit ensuite d'inclure cette liste de dépendance.

include .depend
