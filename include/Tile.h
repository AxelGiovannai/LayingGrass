//
// Created by Axel on 04/11/2024.
//

#ifndef TILES_H
#define TILES_H
#include <vector>


class Tile {
private:
    std::pair <int, int> position;
    std::vector<std::pair<int,int>> shape;
public:
    void set_position(int a, int b);
    void rotate();
};



#endif //TILES_H
