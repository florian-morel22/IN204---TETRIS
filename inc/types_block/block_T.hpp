#ifndef BLOCK_T_HPP
#define BLOCK_T_HPP

#include "../block.hpp"

class Block_T : public Block {

  	public:
    	Block_T(int i, int j);
    	void rotate(Grid &);
};

#endif //! BLOCK_T