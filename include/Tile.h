//
// Created by Axel on 04/11/2024.
//

#ifndef TILES_H
#define TILES_H
#include <vector>


class Tile {
private:
    std::pair <int, int> position;
    std::vector<std::vector<int>> shape;
public:

    Tile(int x, int y, const std::vector<std::vector<int>> &shape);

    [[nodiscard]] std::vector<std::vector<int>> getter_shape() const;
    [[nodiscard]] std::pair<int, int> getter_position() const;
    void set_position(int a, int b);
    void rotate();



};



#endif //TILES_H
