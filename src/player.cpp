#include "player.hpp"
#include "utils.hpp"

namespace tetris {

std::string Player::get_pseudo() const { return pseudo_; };

void Player::set_pseudo(std::string newPseudo) { pseudo_ = newPseudo; }

int Player::get_score() const { return score_; }

void Player::set_score(int newScore) { score_ = newScore; }
}; // namespace tetris