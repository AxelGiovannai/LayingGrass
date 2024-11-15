//
// Created by Axel on 04/11/2024.
//

#include "../include/Player.h"
#include "../include/Tile.h"
#include <vector>
#include <string>

Player::Player(const std::string& name) {
    this->name = name;
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

std::vector<std::vector<int>> Player::getter_tiles_shape(const int i) const {
    return tiles[i].getter_shape();
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