#ifndef BLOCK_Z_HPP
#  define BLOCK_Z_HPP

#include "../block.hpp"

class Block_Z : public Block {

    public:
        Block_Z(int i, int j);
        void rotate(Grid &);
};

#endif // !BLOCK_Z_HPP