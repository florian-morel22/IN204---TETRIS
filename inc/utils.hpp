#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>

#include <SFML/System.hpp>

void transpose(std::vector<sf::Vector2i> &);

bool find_vector(std::vector<sf::Vector2i>, sf::Vector2i);

#endif //! UTILS_HPP