#ifndef BLOCK_I_HPP
# define BLOCK_I_HPP

#include <iostream>
#include <map>

#include <SFML/System.hpp> 
#include <SFML/System/Vector2.hpp>

#include "../block.hpp"

class Block_I : public Block
{
    private:
        
    public:
        Block_I(unsigned int i, unsigned int j);
        void rotate();

};

#endif //!BLOCK_I