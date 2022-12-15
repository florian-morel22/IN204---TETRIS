#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics/Text.hpp>

namespace tetris {

const size_t WIN_WIDTH = 1500;
const size_t WIN_HEIGHT = 1000;
const std::string MY_PATH = "/home/IN204/project";

void transpose(std::vector<sf::Vector2i> &);

bool find_vector(std::vector<sf::Vector2i>, sf::Vector2i);

void setTextCenterPosition(sf::Text &, sf::Vector2f &);

} // namespace tetris

#endif // !UTILS_HPP