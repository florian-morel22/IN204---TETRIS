#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Network.hpp>

namespace tetris {

const size_t WIN_WIDTH = 15000 / 3;
const size_t WIN_HEIGHT = 10000 / 3;
const float e = WIN_WIDTH * 0.02;
const float thickness = WIN_WIDTH * 0.007;
const float L_cases = 0.30 * WIN_WIDTH;

const float H_12 = 0.4 * WIN_HEIGHT;
const float H_13 = 0.3 * WIN_HEIGHT;
const float H_22 = WIN_HEIGHT - 3 * e - H_12 - thickness;
const float H_23 = WIN_HEIGHT - 3 * e - H_13 - thickness;

const float H_32 = 0.8 * WIN_HEIGHT;
const float H_33 = 0.7 * WIN_HEIGHT;
const float H_42 = WIN_HEIGHT - 3 * e - H_32 - thickness;
const float H_43 = WIN_HEIGHT - 3 * e - H_33 - thickness;
const std::string MY_PATH = "/home/ensta/IN204/project";

void transpose(std::vector<sf::Vector2i> &);

bool find_vector(std::vector<sf::Vector2i>, sf::Vector2i);

void setTextCenterPosition(sf::Text &, sf::Vector2f);

void initialize_text(sf::Text &text, sf::Font &font, int type_position,
                     sf::Vector2f pos = {10.f, 10.f},
                     unsigned int charSize = 10, std::string str = "TEXT",
                     sf::Color color = sf::Color(0, 0, 0),
                     sf::Vector2f scale = {1.f, 1.f});

void scaleToMinSize(sf::Sprite &Sprite, float H, float W);

float min(float a, float b);

} // namespace tetris

#endif // !UTILS_HPP