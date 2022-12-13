#ifndef BLOCK_T_HPP
# define BLOCK_T_HPP

# include "../block.hpp"

namespace TETRIS {


class Block_T : public Block {

  	public:
    	Block_T(int i, int j);
    	void rotate(Grid &);
};


} // !namespace TETRIS

#endif // !BLOCK_T_HPP