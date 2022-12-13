#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace TETRIS {


void transpose(std::vector<sf::Vector2i> &);

bool find_vector(std::vector<sf::Vector2i>, sf::Vector2i);

void setTextCenterPosition(sf::Text&, sf::Vector2f&);


} // !namespace TETRIS

#endif // !UTILS_HPP