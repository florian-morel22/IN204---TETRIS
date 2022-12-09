#ifndef BLOCK_O_HPP
# define BLOCK_O_HPP

#include "../block.hpp"

class Block_O : public Block {

    public:
        Block_O(int i, int j);
        void rotate(Grid &);
};

#endif //! BLOCK_O