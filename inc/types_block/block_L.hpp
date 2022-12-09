#ifndef BLOCK_L_HPP
# define BLOCK_L_HPP

#include "../block.hpp"

class Block_L : public Block {

  public:
    Block_L(int i, int j);
    void rotate(Grid &);
};

#endif // !BLOCK_L_hpp