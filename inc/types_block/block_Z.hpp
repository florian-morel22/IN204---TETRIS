#ifndef BLOCK_Z_HPP
# define BLOCK_Z_HPP

# include "../block.hpp"

namespace tetris {


class Block_Z : public Block {

    public:
        Block_Z(int i, int j);
        void rotate(Grid &);
};


} // !namespace tetris

#endif // !BLOCK_Z_HPP