#include "../inc/utils.hpp"

namespace tetris {

void transpose(std::vector<sf::Vector2i> &v) {

  for (size_t i = 0; i < v.size(); i++) {
    int x = v[i].x;
    v[i].x = v[i].y;
    v[i].y = x;
  }
}

bool find_vector(std::vector<sf::Vector2i> list_vectors, sf::Vector2i vector) {
  for (size_t k = 0; k < list_vectors.size(); k++)
    if (list_vectors[k].x == vector.x && list_vectors[k].y == vector.y)
      return true;
  return false;
}

void setTextCenterPosition(sf::Text &txt, sf::Vector2f center) {
  sf::Vector2f offset;

  offset.x = txt.getPosition().x - txt.getGlobalBounds().left -
             txt.getGlobalBounds().width / 2.;
  offset.y = txt.getPosition().y - txt.getGlobalBounds().top -
             txt.getGlobalBounds().height / 2.;

  txt.setPosition(center + offset);
}

void setTextCenterTopPosition(sf::Text &txt, sf::Vector2f center) {
  sf::Vector2f offset;

  offset.x = txt.getPosition().x - txt.getGlobalBounds().left -
             txt.getGlobalBounds().width / 2.;
  offset.y = 0;

  txt.setPosition(center + offset);
}

void setTextCenterBottomPosition(sf::Text &txt, sf::Vector2f center) {
  sf::Vector2f offset;

  offset.x = txt.getPosition().x - txt.getGlobalBounds().left -
             txt.getGlobalBounds().width / 2.;
  offset.y = txt.getPosition().y - txt.getGlobalBounds().top -
             txt.getGlobalBounds().height;

  txt.setPosition(center + offset);
}

void setTextRightTopPosition(sf::Text &txt, sf::Vector2f center) {
  sf::Vector2f offset;

  offset.x = txt.getPosition().x - txt.getGlobalBounds().left -
             txt.getGlobalBounds().width;
  offset.y = 0;

  txt.setPosition(center + offset);
}

void initialize_text(sf::Text &text, sf::Font &font, int type_position,
                     sf::Vector2f pos, unsigned int charSize, std::string str,
                     sf::Color color, sf::Vector2f scale) {
  text.setFont(font);
  text.setString(str);
  text.setCharacterSize(charSize);
  text.setFillColor(color);
  text.setScale(scale);

  /* From where is calculated the pos : center of text, corner top left,
  Middle top ?*/
  if (type_position == 1)
    setTextCenterPosition(text, pos);
  else if (type_position == 2)
    setTextCenterTopPosition(text, pos);
  else if (type_position == 3)
    setTextCenterBottomPosition(text, pos);
  else if (type_position == 4)
    setTextRightTopPosition(text, pos);
  else
    text.setPosition(pos);
}

void scaleToMinSize(sf::Sprite &Sprite, float H, float W) {
  auto bounds = Sprite.getGlobalBounds();
  float rapport_h = H / bounds.height;
  float rapport_w = W / bounds.width;
  if (rapport_h > rapport_w) { // On multiplie par le rapport L/l le plus grand
    Sprite.setScale(rapport_h,
                    rapport_h); // On multiplie largeur et longueur par H/h
  } else {
    Sprite.setScale(rapport_w, rapport_w);
  }
}

float min(float a, float b) {
  if (a < b)
    return a;
  else
    return b;
}

} // namespace tetris