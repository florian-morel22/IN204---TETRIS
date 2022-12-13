#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

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

void setTextCenterPosition(sf::Text &txt, sf::Vector2f& center) 
{   
    sf::Vector2f offset;
    offset.x = txt.getPosition().x - txt.getGlobalBounds().left - txt.getGlobalBounds().width/2.;
    offset.y = txt.getPosition().y - txt.getGlobalBounds().top - txt.getGlobalBounds().height/2.;

    txt.setPosition(center + offset);
}


} // !namespace tetris