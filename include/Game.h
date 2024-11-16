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
    int player_turn = 1;
    int nb_rounds = 0;
    Board game_board;
    std::vector<Player> players;
    std::vector<Tile> tiles;
public:
    [[nodiscard]] int getter_nb_players() const;
    [[nodiscard]] int getter_player_turn() const;
    [[nodiscard]] int getter_nb_rounds() const;
    [[nodiscard]] Board getter_game_board();
    [[nodiscard]] Player getter_players(int i);
    [[nodiscard]] Tile getter_tiles(int i);
    void setter_nb_players(int nb);
    void setter_player_turn();
    void setter_nb_rounds(int nb);
    void setter_game_board();
    void setter_players(const Player& player);
    void setter_tiles(const Tile &tile);
    void place_initial_stones();
    void place_initial_tile_exchanges();
    void place_initial_robberies();
    void place_Rock(Player &player, int x, int y);
    static void generate_tile(Game &game);
    void initialize_game();
};



#endif //GAME_H
