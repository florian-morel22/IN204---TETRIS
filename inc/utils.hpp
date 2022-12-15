#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics/Text.hpp>

namespace tetris {

const size_t WIN_WIDTH = 1500;
const size_t WIN_HEIGHT = 1000;
const std::string MY_PATH = "/home/IN204/project";

void transpose(std::vector<sf::Vector2i> &);

bool find_vector(std::vector<sf::Vector2i>, sf::Vector2i);

void setTextCenterPosition(sf::Text &, sf::Vector2f);

void initialize_text(sf::Text &text, sf::Font &font,
                     sf::Vector2f pos = {10.f, 10.f},
                     unsigned int charSize = 10, std::string str = "TEXT",
                     sf::Color color = sf::Color(0, 0, 0),
                     sf::Vector2f scale = {1.f, 1.f});

} // namespace tetris

#endif // !UTILS_HPP