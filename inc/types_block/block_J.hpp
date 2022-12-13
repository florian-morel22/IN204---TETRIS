#ifndef BLOCK_J_HPP
# define BLOCK_J_HPP

# include "../block.hpp"

namespace TETRIS {


class Block_J : public Block {

    public:
        Block_J(int i, int j);
        void rotate(Grid &);
};


} // !namespace TETRIS

#endif // !BLOCK_J_HPP