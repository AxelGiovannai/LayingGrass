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
private:
    int nb_players = 0;
    int nb_rounds = 0;
    Board game_board;
    std::vector<Player> players;
    std::vector<Tile> tiles;
public:

};



#endif //GAME_H
