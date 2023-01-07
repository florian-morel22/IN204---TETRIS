#include "player.hpp"
#include "utils.hpp"

namespace tetris {

Player::Player() {
  Host_ = false;
  Client_ = false;
  score_ = 0;
  pseudo_ = "player";
}

std::string Player::get_pseudo() const { return pseudo_; };

void Player::set_pseudo(std::string newPseudo) { pseudo_ = newPseudo; }

int Player::get_score() const { return score_; }

void Player::add_score(int points) { score_ = score_ + points; }
void Player::set_score(int new_score) { score_ = new_score; };

bool Player::isHost() const { return Host_; }
void Player::set_Host(bool host) { Host_ = host; }

bool Player::isClient() const { return Client_; }
void Player::set_Client(bool client) { Client_ = client; }
}; // namespace tetris