//
// Created by Axel on 04/11/2024.
//

#ifndef GAME_H
#define GAME_H
#include "Board.h"
#include "Player.h"
#include "Tile.h"
#include <vector>

class Game {
public:
    int nb_players;
    int nb_rounds;
    Board game_board;
    std::vector<Player> players;
    std::vector<Tile> tiles;
private:

};



#endif //GAME_H
