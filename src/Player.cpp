#include "../include/Player.h"
#include "../include/Tile.h"
#include <utility>
#include <vector>
#include <string>
#include <iostream>

Player::Player(std::string name, std::string color, int id) : name(std::move(name)), color(std::move(color)), id(id) {
    starting_tile = {
        {1}
    };
}

std::string Player::getter_color() const {
    return color;
}

std::string& Player::getter_name(){
    return name;
}

int Player::getter_id() const {
    return id;
}

int& Player::getter_tile_exchange(){
    return tile_exchange;
}

void Player::setter_tile_exchange(const int tile_exchange) {
    this->tile_exchange = tile_exchange -1;
}

std::vector<std::vector<int>> Player::getter_starting_tile() const {
    return starting_tile;
}