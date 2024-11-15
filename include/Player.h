//
// Created by Axel on 04/11/2024.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Tile.h"


class Player {
private:
    char name;
    char color{}; // changer ca c'est de la merde séquences d’échappement ANSI
    int tile_exchange = 0;
    bool stone = true;
    bool Robbery = true;
    std::vector<Tile> tiles;
public:
    explicit Player(char name);

    [[nodiscard]] char getter_name() const;
    void getter_color(); // changer ca c'est de la merde séquences d’échappement ANSI
    [[nodiscard]] int getter_tile_exchange() const;
    [[nodiscard]] bool getter_stone() const;
    [[nodiscard]] bool getter_Robbery() const;
    [[nodiscard]] std::vector<std::vector<int>> getter_tiles_shape(int i) const;



};



#endif //PLAYER_H
