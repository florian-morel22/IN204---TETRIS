#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>

#include <SFML/System.hpp>

void transpose(std::vector<sf::Vector2u> &);

bool find_vector(std::vector<sf::Vector2u>, sf::Vector2u);

#endif //! UTILS_HPP