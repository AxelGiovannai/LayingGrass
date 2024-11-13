//
// Created by Axel on 04/11/2024.
//
#include <iostream>
#include "../include/Tile.h"
#include <vector>

std::vector<std::vector<int>> Tile::getter_shape() const {
    return shape;
};





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


void Tile::rotate() {
    const std::size_t n = shape.size();
    for (std::size_t i = 0; i < n / 2; ++i) {
        for (std::size_t j = i; j < n - i - 1; ++j) {
            const int temp = shape[i][j]; shape[i][j] = shape[n - j - 1][i];
            shape[n - j - 1][i] = shape[n - i - 1][n - j - 1];
            shape[n - i - 1][n - j - 1] = shape[j][n - i - 1];
            shape[j][n - i - 1] = temp;
        }
    }
}








//char a la place des booléens