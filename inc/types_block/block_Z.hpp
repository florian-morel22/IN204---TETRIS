#ifndef BLOCK_Z_HPP
# define BLOCK_Z_HPP

# include "../block.hpp"

namespace TETRIS {


class Block_Z : public Block {

    public:
        Block_Z(int i, int j);
        void rotate(Grid &);
};


} // !namespace TETRIS

#endif // !BLOCK_Z_HPP