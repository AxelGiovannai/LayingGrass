//
// Created by Axel on 04/11/2024.
//
#include <iostream>
#include "../include/Tile.h"
#include <vector>


void Tile::set_position(const int a, const int b) {
    this->position.first = a;
    this->position.second = b;
};

void Tile::rotate() {
    std::vector<std::vector<bool>> new_shape(this->shape[0].size(), std::vector<bool>(this->shape.size()));
    for (int i = 0; i < this->shape.size(); i++) {
        for (int j = 0; j < this->shape[i].size(); j++) {
            new_shape[j][i] = this->shape[i][j];
        }
    }
    this->shape = new_shape;
};







//char a la place des booléens