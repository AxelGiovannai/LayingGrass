//
// Created by Axel on 04/11/2024.
//

#ifndef TILES_H
#define TILES_H
#include <vector>


class Tile {
private:
    std::vector<std::vector<int>> shape;
public:

    explicit Tile(const std::vector<std::vector<int>> &shape);
    [[nodiscard]] std::vector<std::vector<int>> getter_shape() const;

    void rotate();
    void flip();


};



#endif //TILES_H
