#ifndef BLOCK_I_HPP
# define BLOCK_I_HPP

# include "../block.hpp"

namespace TETRIS {


class Block_I : public Block {
    
    public:
        Block_I(int i, int j);
        void rotate(Grid &);
};


} // !namespace TETRIS

#endif // !BLOCK_I_HPP