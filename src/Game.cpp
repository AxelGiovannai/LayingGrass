//
// Created by Axel on 04/11/2024.
//

#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/Game.h"

int& Game::getter_nb_players(){
    return nb_players;
}

int& Game::getter_player_turn(){
    return player_turn;
}

int& Game::getter_nb_rounds(){
    return nb_rounds;
}

Board& Game::getter_game_board() {
    return game_board;
}

Player& Game::getter_players(const int i) {
    return players[i];
}

Tile& Game::getter_tiles(const int i) {
    return tiles[i];
}

void Game::setter_nb_players(const int nb) {
    nb_players = nb;
}

void Game::setter_player_turn() {
    player_turn = (player_turn % nb_players) + 1;
    if (player_turn == 1) {
        nb_rounds++;
    }
}

void Game::setter_nb_rounds() {
    this->nb_rounds;
}



void Game::setter_game_board() {
   if (nb_players < 5) {
       game_board.setter_board(20, 20);
   } else {
       game_board.setter_board(30, 30);
   }
    for (auto &row : game_board.getter_board()) {
        std::fill(row.begin(), row.end(), '.');
    }
    place_initial_stones();
    place_initial_tile_exchanges();
    place_initial_robberies();
}

void Game::setter_players(const Player& player) {
    players.push_back(player);
}

void Game::setter_tiles(const Tile& tile) {
    tiles.push_back(tile);
}

void Game::initialize_game() {
    setter_game_board();
    for (auto &player : players) {
        int x, y;
        do {
            x = std::rand() % game_board.getter_board().size();
            y = std::rand() % game_board.getter_board()[0].size();
        } while (game_board.getter_case(x, y) != '.');
        game_board.setter_case(x, y, player.getter_color());
    }
    generate_tile(*this);
}

void Game::place_initial_stones() {
    std::srand(std::time(nullptr));
    const int num_stones = static_cast<int>(std::ceil(nb_players * 0.5));
    for (int i = 0; i < num_stones; ++i) {
        int x, y;
        do {
            x = std::rand() % game_board.getter_board().size();
            y = std::rand() % game_board.getter_board()[0].size();
        } while (game_board.getter_case(x, y) != '.');
        game_board.setter_case(x, y, 'P');
    }
}

void Game::place_initial_tile_exchanges() {
    std::srand(std::time(nullptr));
    const int num_tile_exchanges = static_cast<int>(std::ceil(nb_players * 1.5));
    for (int i = 0; i < num_tile_exchanges; ++i) {
        int x, y;
        do {
            x = std::rand() % game_board.getter_board().size();
            y = std::rand() % game_board.getter_board()[0].size();
        } while (game_board.getter_case(x, y) != '.');
        game_board.setter_case(x, y, 'E');
    }
}

void Game::place_initial_robberies() {
    std::srand(std::time(nullptr));
    const int num_robberies = static_cast<int>(std::ceil(nb_players * 1));
    for (int i = 0; i < num_robberies; ++i) {
        int x, y;
        do {
            x = std::rand() % game_board.getter_board().size();
            y = std::rand() % game_board.getter_board()[0].size();
        } while (game_board.getter_case(x, y) != '.');
        game_board.setter_case(x, y, 'V');
    }
}

void Game::remove_tile(int index) {
    if (index >= 0 && index < tiles.size()) {
        tiles.erase(tiles.begin() + index);
    }
}

void Game::generate_tile(Game &game) {
    std::vector<Tile> All_Shapes;
    All_Shapes.push_back(Tile{{
        {1,0,0},
        {1,1,1},
        {0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0},
        {0,1,0},
        {1,1,1}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0},
        {1,1,1},
        {0,1,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,0,1},
        {1,1,1},
        {1,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0},
        {1,1,1},
        {0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,1},
        {1,1}
    }});

    All_Shapes.push_back(Tile{{
        {1,0,1},
        {1,1,1},
        {0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,1,1},
        {0,0,0},
        {0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0},
        {1,1,0},
        {1,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,0},
        {1,1}
    }});

    All_Shapes.push_back(Tile{{
        {0,0,1},
        {0,1,1},
        {1,1,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,1},
        {0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0,0,0},
        {1,1,0,0,0},
        {1,0,0,0,0},
        {1,0,0,0,0},
        {1,1,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,1,1,0,0},
        {1,0,0,0,0},
        {1,0,0,0,0},
        {1,0,0,0,0},
        {1,0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,0,0,1,0},
        {0,0,0,1,0},
        {0,0,0,1,1},
        {0,1,1,1,0},
        {1,1,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,0,0,1},
        {0,0,1,1},
        {0,1,1,0},
        {0,1,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0},
        {1,1,1},
        {1,1,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,1,1},
        {0,0,0},
        {0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,0,0,0},
        {1,1,0,0},
        {1,0,0,0},
        {1,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,1},
        {1,1,0},
        {1,1,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0},
        {1,1,0},
        {1,1,1}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0,0},
        {0,1,0,0},
        {1,1,1,0},
        {1,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,0},
        {1,1}
    }});

    All_Shapes.push_back(Tile{{
        {1,1,0},
        {1,1,0},
        {1,1,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,1,1,0},
        {0,1,0,0},
        {0,1,0,0},
        {0,1,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,0,0,0},
        {1,1,0,0},
        {0,1,1,0},
        {0,0,1,1}
    }});

    All_Shapes.push_back(Tile{{
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,0,0,0},
        {1,1,1,0},
        {0,0,1,0},
        {0,0,1,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,0,0,0,0},
        {1,1,0,0,0},
        {1,0,0,0,0},
        {1,1,0,0,0},
        {1,0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,0,0,0},
        {1,1,0,0},
        {1,1,0,0},
        {1,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0,0,0},
        {0,1,0,0,0},
        {0,1,0,0,0},
        {1,1,1,0,0},
        {1,0,1,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,1},
        {0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,0,0,0},
        {1,0,0,0},
        {1,1,1,0},
        {1,0,1,1}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0,0,0},
        {0,1,0,0,0},
        {1,1,0,0,0},
        {1,0,0,0,0},
        {1,0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,1,0,0,0},
        {0,1,0,0,0},
        {0,1,1,1,0},
        {1,1,0,0,0},
        {1,0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,0,0,0},
        {1,0,0,0},
        {1,1,0,0},
        {1,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0},
        {1,1,0},
        {1,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,0,0,1},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,0,0,1,1},
        {1,0,0,0,1},
        {1,1,1,1,1},
        {0,0,0,0,0},
        {0,0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,0,0,0},
        {1,0,0,0},
        {1,1,0,0},
        {0,1,1,1}
    }});

    All_Shapes.push_back(Tile{{
        {1,1,0,0,0},
        {0,1,1,0,0},
        {1,1,0,0,0},
        {0,1,1,0,0},
        {0,1,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,0,0},
        {1,1,0},
        {1,1,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0,0},
        {0,1,0,0},
        {1,1,1,1},
        {0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,1},
        {1,1}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0,0},
        {1,1,0,0},
        {1,1,0,0},
        {1,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,1,1},
        {0,1,0},
        {1,1,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0},
        {1,1,1},
        {0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,0,0,0},
        {1,0,0,0},
        {1,1,1,1},
        {0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0,0},
        {1,1,0,0},
        {1,0,0,0},
        {1,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,0,0},
        {1,1,1},
        {0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,0,0,0,0},
        {1,1,0,0,0},
        {1,0,0,0,0},
        {1,0,0,0,0},
        {1,0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,0,1,1,1},
        {0,0,1,0,0},
        {0,0,1,0,0},
        {0,0,1,0,0},
        {1,1,1,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0,0,0,0},
        {0,1,0,0,0,0},
        {1,1,0,0,0,0},
        {1,0,0,0,0,0},
        {1,1,0,0,0,0},
        {1,0,0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,1,0,0},
        {0,1,0,0},
        {0,1,1,1},
        {0,0,0,1}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0,0,0},
        {0,1,0,0,0},
        {1,1,1,0,0},
        {0,1,0,0,0},
        {0,1,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,0,1},
        {0,0,1},
        {1,1,1}
    }});

    All_Shapes.push_back(Tile{{
        {0,0,1,0,0},
        {0,0,1,0,0},
        {0,0,1,0,0},
        {0,0,1,0,0},
        {0,0,1,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,0,1,0},
        {1,1,1,0},
        {0,1,0,0},
        {1,1,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,0,1,0},
        {1,1,1,0},
        {0,1,1,1},
        {0,1,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,1,1},
        {0,1,0,0},
        {0,1,0,0},
        {1,1,1,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,0,0,0,0},
        {1,0,0,0,0},
        {1,1,0,0,0},
        {1,0,0,0,0},
        {1,0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,1,0,0},
        {0,1,0,0},
        {0,1,0,1},
        {1,1,1,1}
    }});

    All_Shapes.push_back(Tile{{
        {0,0,1,0,0},
        {0,1,1,0,0},
        {1,1,0,0,0},
        {1,0,0,0,0},
        {1,1,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,1,0,0,0},
        {0,1,0,0,0,0},
        {0,1,0,0,0,0},
        {0,1,0,0,0,0},
        {1,1,0,0,0,0},
        {1,0,0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,0,1,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,1,0,0},
        {0,1,0,1},
        {0,1,0,1},
        {0,1,1,1}
    }});

    All_Shapes.push_back(Tile{{
        {1,0,0,0,0},
        {1,1,0,0,0},
        {1,0,0,0,0},
        {1,0,0,0,0},
        {1,0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,0,0,0,0},
        {1,0,1,0,0},
        {1,1,1,1,0},
        {0,1,0,0,0},
        {0,1,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,1,0,0,0,0,0},
        {1,0,0,0,0,0,0},
        {1,0,0,0,0,0,0},
        {1,0,0,0,0,0,0},
        {1,0,0,0,0,0,0},
        {1,0,0,0,0,0,0},
        {1,0,0,0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0,0},
        {1,1,1,0},
        {1,0,0,0},
        {1,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,1},
        {0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,0,1},
        {1,0,1},
        {1,1,1}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0},
        {1,1,1},
        {1,0,1}
    }});

    All_Shapes.push_back(Tile{{
        {0,0,1,0,0},
        {0,0,1,0,0},
        {1,1,1,1,1},
        {0,0,1,0,0},
        {0,0,1,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,0,0,1,0,0},
        {0,0,1,1,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0},
        {0,1,1,0,0,0},
        {1,1,0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,1,0,0,0},
        {1,0,0,0,0},
        {1,1,0,0,0},
        {1,0,0,0,0},
        {1,1,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0,0,0},
        {0,1,0,0,0},
        {0,1,0,0,0},
        {1,1,1,1,1},
        {0,1,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0,0,0},
        {1,1,0,0,0},
        {1,0,0,0,0},
        {1,0,0,0,0},
        {1,0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,1,0},
        {0,1,0,0},
        {1,1,0,0},
        {1,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,1,0,0,0},
        {0,1,0,0,0,0},
        {1,1,0,0,0,0},
        {0,1,1,0,0,0},
        {0,1,0,0,0,0},
        {0,1,0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,1,0,0,0,0},
        {1,1,0,0,0,0},
        {0,1,0,0,0,0},
        {0,1,1,0,0,0},
        {0,1,0,0,0,0},
        {0,1,0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0,0},
        {0,1,1,0},
        {1,1,0,0},
        {0,1,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,1,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,0,1,1},
        {1,1,1,0},
        {1,0,0,0},
        {1,1,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,1,0},
        {0,1,0,0},
        {0,1,0,0},
        {1,1,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0,0},
        {0,1,0,0},
        {1,1,1,0},
        {0,1,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,1,1,0},
        {1,0,1,0},
        {1,0,0,0},
        {1,1,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0,0},
        {0,1,1,0},
        {1,1,0,0},
        {1,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {1,0,0},
        {1,1,0},
        {1,1,1}
    }});

    All_Shapes.push_back(Tile{{
        {1,0,0,0},
        {1,0,0,0},
        {1,0,0,0},
        {1,1,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0,0},
        {1,1,1,1},
        {1,0,0,0},
        {0,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,1,0},
        {1,1,0,0},
        {1,0,0,0},
        {1,0,0,0}
    }});

    All_Shapes.push_back(Tile{{
        {0,1,0,0},
        {1,1,0,0},
        {1,0,0,0},
        {1,1,0,0}
    }});
    All_Shapes.push_back(Tile{{
        {1,1,0,0},
        {1,0,0,0},
        {1,1,0,0},
        {0,1,0,0}
    }});

    const int num_tiles = static_cast<int>(std::ceil(game.getter_nb_players() * 10.67));
    for (int i = 0; i < num_tiles; ++i) {
        const int random = std::rand() % All_Shapes.size();
        game.setter_tiles(All_Shapes[random]);
    }

}




