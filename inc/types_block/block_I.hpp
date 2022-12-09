#ifndef BLOCK_I_HPP
# define BLOCK_I_HPP

# include "../block.hpp"

class Block_I : public Block {
    
    public:
        Block_I(int i, int j);
        void rotate(Grid &);
};

#endif // !BLOCK_I_HPP