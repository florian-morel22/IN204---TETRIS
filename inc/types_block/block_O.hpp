#ifndef BLOCK_O_HPP
# define BLOCK_O_HPP

#include <iostream>
#include <map>

#include <SFML/System.hpp> 
#include <SFML/System/Vector2.hpp>

#include "../block.hpp"

class Block_O : public Block
{
    private:
        
    public:
        Block_O(unsigned int i, unsigned int j);
        void rotate();

};

#endif //!BLOCK_O