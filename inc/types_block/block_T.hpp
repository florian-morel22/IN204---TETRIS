#ifndef BLOCK_T_HPP
#define BLOCK_T_HPP

#include "../block.hpp"

namespace tetris {

class Block_T : public Block {

public:
  Block_T(int i, int j);
  void rotate(Grid &);
};

} // namespace tetris

#endif // !BLOCK_T_HPP