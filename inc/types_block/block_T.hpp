#ifndef BLOCK_T_HPP
#define BLOCK_T_HPP

#include <iostream>
#include <map>

#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>

#include "../block.hpp"

class Block_T : public Block {
private:
public:
  Block_T(unsigned int i, unsigned int j);
  void rotate(Grid &);
};

#endif //! BLOCK_T