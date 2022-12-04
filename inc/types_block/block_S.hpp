#ifndef BLOCK_S_HPP
# define BLOCK_S_HPP

#include <iostream>
#include <map>

#include <SFML/System.hpp> 
#include <SFML/System/Vector2.hpp>

#include "../block.hpp"

class Block_S : public Block
{
    private:
        
    public:
        Block_S(unsigned int i, unsigned int j);
        void rotate(Grid&);

};

#endif //!BLOCK_S