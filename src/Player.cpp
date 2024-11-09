//
// Created by Axel on 04/11/2024.
//

#include "../include/Player.h"


Player::Player(const char * str) {
    //prout
}




char Player::getter_name() const {
    return *name;
}

int Player::getter_tile_exchange() const {
    return tile_exchange;
}

bool Player::getter_stone() const {
    return stone;
}

bool Player::getter_Robbery() const {
    return Robbery;
}



