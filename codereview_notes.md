# Tuesday 6 dec : Tetris project review #

## Project form ##

* Ideally, everything in english
* cmakecache should not be changed manually, only a "cmake" should be needed*
  --> Otherwise it can't be automatically built by a toolchain
* code documentation should not be in a readme, see doxygen
* src/.DS_STORE file ???
* Where is the cmake ?

## Code review ##

* Do not put relative path in the include (like "../inc/game.hpp")
  --> It's the job of the buildchain to handle path, or else it's tied to hierarchy of files
* Carefull with coding style
  --> space between function name and parenthesis ? (main.cpp vs game.cpp)
  --> return after parenthesis ? (avoid mixing one liners)
  --> Putting // !BLOCK_HPP one each or none
* Put template in upper case, this is regular practice (`template <typename TYPE_GRID>`) :white_check_mark:
* You could use a namespace for your project
  --> `namespace tetris {...}` so your constants are not in global scope (some library have some too) :white_check_mark:

```cpp
#include "inc/game.hpp"

int main (){
    Tetris::Game game;
	
    game.Run();
    return 0;
}
```

### main.cpp ###

* No unneeded includes (ideally comment why with a // comment)
  --> `#include <cstdio> // std::cout`
* Put a line break after variable definition
* Space out the code, (space before/after operators such as ==,+,-,const,...)

### game.{cpp,hpp} ###

* use size_t for unsigned constant :white_check_mark:
```cpp
const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 800;
```

* See __PRETTY_FUNCTION__ for easier debug time

```cpp
#include <cstdio>

template <typename T = int>
class Game {
public:
  Game() {
    printf("Ctors 1: %s\n", __PRETTY_FUNCTION__);
  }
  Game(int i) {
    printf("Ctors 2: %s\n", __PRETTY_FUNCTION__);
  }
};

int main()
{
  Game<int> g1;
  Game<char> g2(1);
* Document the includes, especially SMFL + don't mix std includes and SFML
* `void Game::Run()`
  --> This looks like a ctors + run + dtors, do a proper class
* `bool _running = true;`. Don't do that, init in the ctors are at runtime it's not a static variable
  --> Keep the header clean, this form is only ok if you have a POD (ie: a structure with no ctors)
* `l27: TETRIS` avoid hardcoded string if possible (can't be changed easily)
  --> Put all the "variables", at least on top of the function so they are grouped up and 
	  you can split data from code function.
	  
```Cpp
void Game::Initialize()
{
	std::string const window_title = "TETRIS";
	
    window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), window_title, sf::Style::Close);
```

* `std::srand()`, use C++ random when possible
* don't use `NULL`, use `nullptr` (first is an untyped define, the other is a null pointer) :white_check_mark:
* `new` is not catched for memory allocation error
* don't use `unsigned int`, way too verbose and error prone, use `size_t`, it's designed for that :white_check_mark:
* Use smart pointers to wrap allocated memory when possible

* `unsigned int** get_grid_num()const;`: NO, please ><
  --> This is a violation of the const, if you want to modify the object do it within the class (otherwise you let a someone else modify your content, this is dirty) :white_check_mark:

* `if (clock.getElapsedTime().asMilliseconds() > (1000 / fps_grid))`
  --> You can also put the condition in a variable to make it more readable :white_check_mark:

```Cpp
	size_t has_timed_out = clock.getElapsedTime().asMilliseconds() > (1000 / fps_grid);
	if (has_timed_out) // Much easier to review
	{/*...*/}
```

* `void Game::generate_new_block()`: A switch would be better than a list of if/elseif/else :white_check_mark:
  --> https://en.cppreference.com/w/cpp/language/enum
* Same for input handler (multiple if in chain ? Can many trigger at once ?)

### block.{cpp,hpp} ###

* careful for unneded includes
* `   protected: //Les classes qui en heritent en ont besoin`
  --> C++ common knowledge, no need to comment it :white_check_mark:
* `#include <map>` : No map used in the header, but std::vector<>
* might be overkill to get a full class for each block, might want to have a single file also since
  this is mostly the same level of code.

### grid.{cpp,hpp} ###

* `grid_num = new unsigned int* [nb_columns+4];` :white_check_mark:
* `grid_drawn[i][j].setSize({30/(0.7*WIN_WIDTH)*WIN_HEIGHT,30});`
  --> Hard to read, please move parameter to variable. why 30 ? why 0.7 ? why +4 ? :white_check_mark:
  
* Unless your code is 100% failsafe, don't set attributes first. Make it last once you are sure it's done (transactional code and exception safety level, if one of the new fail, your Grid object is corrupted)
```cpp
void Grid::initialize_grid(unsigned int c, unsigned int l){
    nb_lines = l;
    nb_columns = c;
```

* put the color in a variable at the start of the function, avoid hardcoded values
```cpp
    list_color_block.push_back({255,255,255}); // Couleur des cases vides
    list_color_block.push_back({180,167,214}); // Couleur du block I
    list_color_block.push_back({180,167,189}); // ...
    list_color_block.push_back({213,166,189}); // ..
    list_color_block.push_back({182,215,168}); // .
    list_color_block.push_back({249,203,156});
    list_color_block.push_back({234,153,153});
```

* std::vector<sf::Vector2u> is passed by copy, big memory and copy cost, especially for a vector
* you need a `const` over there too
* Also, don't use the "free" name in your function, confusing we can think it's freeing stuff. :white_check_mark:
  --> Rename as "empty" or "clear"
```bash
inc/grid.hpp
41:        bool free_case(unsigned int i, unsigned int j, std::vector<sf::Vector2u> list_squares);

src/grid.cpp
148:bool Grid::free_case(unsigned int i, unsigned int j, std::vector<sf::Vector2u> list_squares){

src/types_block/block_L.cpp
26:        if(G.free_case(i,j-1, list_squares) && G.free_case(i,j, list_squares) &&
27:           G.free_case(i,j+1, list_squares) && G.free_case(i+1,j+1, list_squares) ){
41:        if(G.free_case(i+1,j, list_squares) && G.free_case(i,j, list_squares) &&
42:           G.free_case(i-1,j, list_squares) && G.free_case(i-1,j+1, list_squares) ){
56:        if(G.free_case(i,j+1, list_squares) && G.free_case(i,j, list_squares) &&
57:           G.free_case(i,j-1, list_squares) && G.free_case(i-1,j-1, list_squares) ){
71:        if(G.free_case(i-1,j, list_squares) && G.free_case(i,j, list_squares) &&
72:           G.free_case(i+1,j, list_squares) && G.free_case(i+1,j-1, list_squares) ){
```
