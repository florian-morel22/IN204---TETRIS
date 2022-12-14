#ifndef BLOCK_J_HPP
#define BLOCK_J_HPP

#include "../block.hpp"

namespace tetris {

class Block_J : public Block {

public:
  Block_J(int i, int j);
  void rotate(Grid &);
};

} // namespace tetris

#endif // !BLOCK_J_HPP