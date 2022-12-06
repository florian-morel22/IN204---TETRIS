#ifndef BLOCK_Z_HPP
#define BLOCK_Z_HPP

#include <iostream>
#include <map>

#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>

#include "../block.hpp"

class Block_Z : public Block {
private:
public:
  Block_Z(unsigned int i, unsigned int j);
  void rotate(Grid &);
};

#endif //! BLOCK_Z