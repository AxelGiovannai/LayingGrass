//
// Created by Axel on 04/11/2024.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Tile.h"
#include <iostream>

class Player {
private:
    std::string name;
    char color{}; // changer ca c'est de la merde séquences d’échappement ANSI
    int tile_exchange = 1;
    int stone = 0;
    int Robbery = 0;
    std::vector<Tile> tiles;
public:
    explicit Player(const std::string &name);




    [[nodiscard]] std::string getter_name() const;
    void getter_color(); // changer ca c'est de la merde séquences d’échappement ANSI
    [[nodiscard]] int getter_tile_exchange() const;
    [[nodiscard]] int getter_stone() const;
    [[nodiscard]] int getter_Robbery() const;
    [[nodiscard]] std::vector<std::vector<int>> getter_tiles_shape(int i) const;



};



#endif //PLAYER_H
