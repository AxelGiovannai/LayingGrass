#include "../include/Player.h"
#include "../include/Tile.h"
#include <vector>
#include <string>
#include <iostream>

Player::Player(const std::string& name, char color) : name(name), color(color) {}

char Player::getter_color() const {
    return color;
}

std::vector<std::vector<int>> Player::getter_starting_tile() const {
    return starting_tile;
}

std::string Player::getter_name() const {
    return name;
}

int Player::getter_tile_exchange() const {
    return tile_exchange;
}

int Player::getter_stone() const {
    return stone;
}

int Player::getter_robbery() const {
    return robbery;
}


void Player::setter_tile_exchange(const int tile_exchange) {
    this->tile_exchange = tile_exchange;
}

void Player::setter_stone(const int stone) {
    this->stone = stone;
}

void Player::setter_robbery(const int robbery) {
    this->robbery = robbery;
}

