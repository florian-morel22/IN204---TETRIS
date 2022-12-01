#ifndef BLOCK_L_HPP
# define BLOCK_L_HPP

#include <iostream>
#include <map>

#include <SFML/System.hpp> 
#include <SFML/System/Vector2.hpp>

#include "block.hpp"

class Block_L : public Block
{
    private:
        
    public:
        Block_L(unsigned int i, unsigned int j);
        void rotate();

};

#endif //!BLOCK_L