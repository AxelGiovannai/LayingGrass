//
// Created by Axel on 04/11/2024.
//

#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/Game.h"

int Game::getter_nb_players() const {
    return nb_players;
}

int Game::getter_player_turn() const {
    return player_turn;
}

int Game::getter_nb_rounds() const {
    return nb_rounds;
}

Board Game::getter_game_board() {
    return game_board;
}

Player Game::getter_players(const int i) {
    return players[i];
}

Tile Game::getter_tiles(const int i) {
    return tiles[i];
}

void Game::setter_nb_players(const int nb) {
    nb_players = nb;
}

void Game::setter_player_turn() {
    player_turn = (player_turn % nb_players) + 1;
}

void Game::setter_nb_rounds(const int nb) {
    nb_rounds = nb;
}

void Game::setter_game_board() {
   if (nb_players < 5) {
       game_board.setter_board(20, 20);
   } else {
       game_board.setter_board(30, 30);
   }
    for (auto &row : game_board.getter_board()) {
        std::ranges::fill(row, '.');
    }
    place_initial_stones();
    place_initial_tile_exchanges();
    place_initial_robberies();
}

void Game::setter_players(const Player& p) {
    players.push_back(p);
}

void Game::setter_tiles(const Tile& t) {
    tiles.push_back(t);
}



void Game::place_initial_stones() {
    std::srand(std::time(nullptr));
    const int num_stones = static_cast<int>(std::ceil(nb_players * 0.5)); // 0.5 stone per player, rounded up
    for (int i = 0; i < num_stones; ++i) {
        int x, y;
        do {
            x = std::rand() % game_board.getter_board().size();
            y = std::rand() % game_board.getter_board()[0].size();
        } while (game_board.getter_case(x, y) != '.');
        game_board.setter_case(x, y, 'S');
    }
}

void Game::place_initial_tile_exchanges() {
    std::srand(std::time(nullptr));
    const int num_tile_exchanges = static_cast<int>(std::ceil(nb_players * 1.5)); // 1.5 tile exchange per player, rounded up
    for (int i = 0; i < num_tile_exchanges; ++i) {
        int x, y;
        do {
            x = std::rand() % game_board.getter_board().size();
            y = std::rand() % game_board.getter_board()[0].size();
        } while (game_board.getter_case(x, y) != '.');
        game_board.setter_case(x, y, 'T');
    }
}

void Game::place_initial_robberies() {
    std::srand(std::time(nullptr));
    const int num_robberies = static_cast<int>(std::ceil(nb_players * 1)); // 1 robbery per player, rounded up
    for (int i = 0; i < num_robberies; ++i) {
        int x, y;
        do {
            x = std::rand() % game_board.getter_board().size();
            y = std::rand() % game_board.getter_board()[0].size();
        } while (game_board.getter_case(x, y) != '.');
        game_board.setter_case(x, y, 'R');
    }
}




