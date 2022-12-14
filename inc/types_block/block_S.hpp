#ifndef BLOCK_S_HPP
#define BLOCK_S_HPP

#include "../block.hpp"

namespace tetris {

class Block_S : public Block {

public:
  Block_S(int i, int j);
  void rotate(Grid &);
};

} // namespace tetris

#endif // !BLOCK_S_HPP