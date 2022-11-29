#include <SFML/System.hpp>
#include <vector>

#include "../inc/utils.hpp"

void transpose(std::vector<sf::Vector2u> &v){

    for(size_t i = 0; i<v.size(); i++){
        int x = v[i].x;
        v[i].x = v[i].y;
        v[i].y = x;
    }
}

