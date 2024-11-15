//
// Created by Axel on 04/11/2024.
//
#include <iostream>
#include "../include/Tile.h"
#include <vector>

std::vector<std::vector<int>> Tile::getter_shape() const {
    return shape;
};

Tile::Tile(const std::vector<std::vector<int>> &shape) {
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

void Tile::flip() {
    const std::size_t n = shape.size();
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n / 2; ++j) {
            const int temp = shape[i][j]; shape[i][j] = shape[i][n - j - 1];
            shape[i][n - j - 1] = temp;
        }
    }
}