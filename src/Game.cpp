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
        game_board.setter_case(x, y, player.getter_color()[0]); // Use the first character of the color string
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
        game_board.setter_case(x, y, 'P'); // 'P' for stone
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
        game_board.setter_case(x, y, 'E'); // 'E' for tile exchange
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
        game_board.setter_case(x, y, 'V'); // 'V' for robbery
    }
}

void Game::remove_tile(int index) {
    if (index >= 0 && index < tiles.size()) {
        tiles.erase(tiles.begin() + index);
    }
}

void Game::use_tile_exchange(int tile_index) {
    Player &current_player = getter_players(getter_player_turn() - 1);

    if (current_player.getter_tile_exchange() <= 0) {
        std::cout << "You don't have any tile exchange left!" << std::endl;
        return;
    }

    if (tile_index < 0 || tile_index >= tiles.size()) {
        std::cout << "Invalid tile index!" << std::endl;
        return;
    }

    std::vector<Tile> new_tiles;
    for (int i = tile_index; i < tiles.size(); ++i) {
        new_tiles.push_back(tiles[i]);
    }
    for (int i = 0; i < tile_index; ++i) {
        new_tiles.push_back(tiles[i]);
    }
    tiles = new_tiles;

    current_player.setter_tile_exchange(current_player.getter_tile_exchange() - 1);
}

void Game::apply_bonus_effects() {
    for (int i = 1; i < game_board.getter_board().size() - 1; ++i) {
        for (int j = 1; j < game_board.getter_board()[i].size() - 1; ++j) {
            if (game_board.getter_case(i, j) == 'E' || game_board.getter_case(i, j) == 'V' || game_board.getter_case(i, j) == 'P') {
                char bonus = game_board.getter_case(i, j);
                char surrounding_char = game_board.getter_case(i-1, j);
                bool surrounded_by_same_char = true;

                for (int x = -1; x <= 1; ++x) {
                    for (int y = -1; y <= 1; ++y) {
                        if (x != 0 || y != 0) {
                            if (game_board.getter_case(i + x, j + y) != surrounding_char) {
                                surrounded_by_same_char = false;
                                break;
                            }
                        }
                    }
                    if (!surrounded_by_same_char) break;
                }

                if (surrounded_by_same_char) {
                    game_board.setter_case(i, j, surrounding_char);

                    switch (bonus) {
                        case 'E':
                            getter_players(surrounding_char - '0' - 1).increase_tile_exchange();
                            break;
                        case 'V':
                            // Add logic for 'V' bonus if needed
                            break;
                        case 'P':
                            int x, y;
                            do {
                                std::cout << "Enter the coordinates of the empty cell to transform into 'S' (x y): ";
                                std::cin >> x >> y;
                            } while (x < 1 || x > game_board.getter_board().size() || y < 1 || y > game_board.getter_board()[0].size() || game_board.getter_case(x-1, y-1) != '.');
                            game_board.setter_case(x-1, y-1, 'S');
                            break;
                    }
                }
            }
        }
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




