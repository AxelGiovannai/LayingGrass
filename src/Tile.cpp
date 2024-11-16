//
// Created by Axel on 04/11/2024.
//
#include <iostream>
#include "../include/Tile.h"
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> Tile::getter_shape() const {
    return shape;
};

void Tile::setter_shape(const std::vector<std::vector<int>> &shape) {
    this->shape = shape;
};

Tile::Tile(const std::vector<std::vector<int>> &shape) {
    this->shape = shape;
};



void Tile::rotate() {
    const std::size_t rows = shape.size();
    const std::size_t cols = shape[0].size();
    std::vector<std::vector<int>> rotated(cols, std::vector<int>(rows));
    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            rotated[j][rows - 1 - i] = shape[i][j];
        }
    }
    shape = rotated;
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