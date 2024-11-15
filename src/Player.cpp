//
// Created by Axel on 04/11/2024.
//

#include "../include/Player.h"
#include "../include/Tile.h"
#include <vector>


Player::Player(const char name) {
    this->name = name;

}




char Player::getter_name() const {
    return name;
}

int Player::getter_tile_exchange() const {
    return tile_exchange;
}

int Player::getter_stone() const {
    return stone;
}

int Player::getter_Robbery() const {
    return Robbery;
}

std::vector<std::vector<int>> Player::getter_tiles_shape(const int i) const {
    return tiles[i].getter_shape();
}


