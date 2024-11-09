//
// Created by Axel on 04/11/2024.
//

#include "../include/Game.h"

#include <iostream>

int Game::getter_nb_players() const {
    return nb_players;
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

void Game::setter_nb_rounds(const int nb) {
    nb_rounds = nb;
}

void Game::setter_game_board() {
   // game_board.setter_case();
}

void Game::setter_players(const Player& p) {
    players.push_back(p);
}

void Game::setter_tiles(const Tile& t) {
    tiles.push_back(t);
}

void Game::display_board() {
    for (const std::vector<std::vector<char>> board = game_board.getter_board(); const auto & i : board) {
        for (const char j : i) {
            std::cout << j;
        }
        std::cout << std::endl;
    }
}

