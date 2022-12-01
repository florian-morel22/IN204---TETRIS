#ifndef UTILS_HPP
# define UTILS_HPP

#include <SFML/System.hpp>
#include <vector>

void transpose(std::vector<sf::Vector2u> &);

bool find_vector(std::vector<sf::Vector2u>, sf::Vector2u);

#endif //!UTILS_HPP