#include "../include/Player.h"
#include "../include/Tile.h"
#include <utility>
#include <vector>
#include <string>
#include <iostream>

Player::Player(std::string name, const char color) : name(std::move(name)), color(color) {}

char Player::getter_color() const {
    return color;
}

std::string& Player::getter_name(){
    return name;
}

int& Player::getter_tile_exchange(){
    return tile_exchange;
}

void Player::setter_tile_exchange(const int tile_exchange) {
    this->tile_exchange = tile_exchange -1;
}



