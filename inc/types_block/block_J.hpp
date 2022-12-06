#ifndef BLOCK_J_HPP
#define BLOCK_J_HPP

#include <iostream>
#include <map>

#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>

#include "../block.hpp"

class Block_J : public Block {
private:
public:
  Block_J(unsigned int i, unsigned int j);
  void rotate(Grid &);
};

#endif //! BLOCK_J