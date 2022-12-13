#ifndef BLOCK_S_HPP
# define BLOCK_S_HPP

# include "../block.hpp"

namespace TETRIS {


class Block_S : public Block {

    public:
        Block_S(int i, int j);
        void rotate(Grid &);
};


} // !namespace TETRIS

#endif // !BLOCK_S_HPP