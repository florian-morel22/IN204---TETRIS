#ifndef BLOCK_O_HPP
#define BLOCK_O_HPP

#include "../block.hpp"

namespace tetris {

class Block_O : public Block {

public:
  Block_O(int i, int j);
  void rotate(Grid &);
};

} // namespace tetris

#endif // !BLOCK_O_HPP