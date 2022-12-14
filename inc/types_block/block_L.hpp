#ifndef BLOCK_L_HPP
#define BLOCK_L_HPP

#include "../block.hpp"

namespace tetris {

class Block_L : public Block {

public:
  Block_L(int i, int j);
  void rotate(Grid &);
};

} // namespace tetris

#endif // !BLOCK_L_HPP