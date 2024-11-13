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
// Constructor implementation
Tile::Tile(const int x, const int y, const std::vector<std::vector<int>> &shape) {
    this->position.first = x;
    this->position.second = y;
    this->shape = shape;
};


void Tile::rotate() {    // vraiment approximative
    std::vector<std::pair<int, int>> new_shape;
    for (auto &[fst, snd] : this->shape) {
        new_shape.emplace_back(snd, -fst);
    }
    this->shape = new_shape;

};








//char a la place des booléens