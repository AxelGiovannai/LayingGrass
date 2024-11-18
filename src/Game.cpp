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
            x = std::rand() % (game_board.getter_board().size() - 2) + 1; // Avoid borders
            y = std::rand() % (game_board.getter_board()[0].size() - 2) + 1; // Avoid borders
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
            x = std::rand() % (game_board.getter_board().size() - 2) + 1; // Avoid borders
            y = std::rand() % (game_board.getter_board()[0].size() - 2) + 1; // Avoid borders
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
            x = std::rand() % (game_board.getter_board().size() - 2) + 1; // Avoid borders
            y = std::rand() % (game_board.getter_board()[0].size() - 2) + 1; // Avoid borders
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
            char cell = game_board.getter_case(i, j);
            if (cell == 'E' || cell == 'V' || cell == 'P') {
                char surrounding_char = game_board.getter_case(i-1, j);
                bool surrounded_by_same_char = true;


                if ((i > 0 && game_board.getter_case(i-1, j) != surrounding_char) ||
                    (i < game_board.getter_board().size() - 1 && game_board.getter_case(i+1, j) != surrounding_char) ||
                    (j > 0 && game_board.getter_case(i, j-1) != surrounding_char) ||
                    (j < game_board.getter_board()[0].size() - 1 && game_board.getter_case(i, j+1) != surrounding_char)) {
                    surrounded_by_same_char = false;
                    }

                if (surrounded_by_same_char && surrounding_char != '.') {
                    game_board.setter_case(i, j, surrounding_char);

                    switch (cell) {
                        case 'E':
                            getter_players(surrounding_char - '0' - 1).increase_tile_exchange();
                            break;
                        case 'V':
                            int enemy_id, x, y;
                            std::cout << "Enter the ID of the player to steal a tile from: ";
                            std::cin >> enemy_id;
                            if (enemy_id >= 1 && enemy_id <= nb_players && enemy_id != surrounding_char - '0') {
                                Player &enemy_player = getter_players(enemy_id - 1);
                                std::cout << "Enter the coordinates of the tile to steal:" << std::endl;
                                do {
                                    std::cout << "X: ";
                                    std::cin >> x;
                                } while (x < 1 || x > game_board.getter_board().size());
                                do {
                                    std::cout << "Y: ";
                                    std::cin >> y;
                                } while (y < 1 || y > game_board.getter_board()[0].size());
                                if (game_board.getter_case(x-1, y-1) == '0' + enemy_id) {
                                    game_board.setter_case(x-1, y-1, '.'); // Remove tile from enemy
                                    int new_x, new_y;
                                    std::cout << "Enter the coordinates to place the stolen tile:" << std::endl;
                                    do {
                                        std::cout << "X: ";
                                        std::cin >> new_x;
                                    } while (new_x < 1 || new_x > game_board.getter_board().size());
                                    do {
                                        std::cout << "Y: ";
                                        std::cin >> new_y;
                                    } while (new_y < 1 || new_y > game_board.getter_board()[0].size());
                                    if (game_board.getter_case(new_x-1, new_y-1) == '.') {
                                        game_board.setter_case(new_x-1, new_y-1, surrounding_char); // Place tile in player's territory
                                    } else {
                                        std::cout << "Invalid placement coordinates!" << std::endl;
                                    }
                                } else {
                                    std::cout << "Invalid tile coordinates!" << std::endl;
                                }
                            } else {
                                std::cout << "Invalid player ID!" << std::endl;
                            }
                            break;
                        case 'P':
                            std::cout << "Enter the coordinates of the empty cell to transform into 'P' (x y):" << std::endl;
                            do {
                                std::cout << "X: ";
                                std::cin >> x;
                            } while (x < 1 || x > game_board.getter_board().size());
                            do {
                                std::cout << "Y: ";
                                std::cin >> y;
                            } while (y < 1 || y > game_board.getter_board()[0].size() || game_board.getter_case(x-1, y-1) != '.');
                            game_board.setter_case(y-1, x-1, 'P');
                            break;
                    }
                }
            }
        }
    }
}

int Game::largest_square_covered(char player_id) {
    int max_square_size = 0;
    const auto &board = game_board.getter_board();
    int n = board.size();
    int m = board[0].size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(m, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (board[i][j] == player_id) {
                dp[i][j] = 1;
                if (i > 0 && j > 0) {
                    dp[i][j] += std::min(std::min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]);
                }
                max_square_size = std::max(max_square_size, dp[i][j]);
            }
        }
    }
    return max_square_size;
}

int Game::count_grass_squares(char player_id) {
    int grass_count = 0;
    const auto &board = game_board.getter_board();
    for (const auto &row : board) {
        for (const auto &cell : row) {
            if (cell == player_id) {
                grass_count++;
            }
        }
    }
    return grass_count;
}

void Game::victory() {

    int max_square_size = 0;
    int max_grass_count = 0;
    int winner_id = -1;

    for (int i = 0; i < nb_players; ++i) {
        char player_id = static_cast<char>(i + 1);
        int square_size = largest_square_covered(player_id);
        int grass_count = count_grass_squares(player_id);

        if (square_size > max_square_size || (square_size == max_square_size && grass_count > max_grass_count)) {
            max_square_size = square_size;
            max_grass_count = grass_count;
            winner_id = i + 1;
        }
    }

    if (winner_id != -1) {
        std::cout << "Player " << winner_id << " wins!" << std::endl;
    } else {
        std::cout << "No winner!" << std::endl;
    }
}

void Game::use_final_exchange(Game &game) {
    for (int i = 0; i < game.nb_players; ++i) {
        Player &player = game.getter_players(i);
        while (player.getter_tile_exchange() > 0) {
            int x, y;
            char choice;
            std::cout << "Player " << player.getter_id() << " (" << player.getter_name() << "), you have " << player.getter_tile_exchange() << " tile exchanges left." << std::endl;
            std::cout << "Do you want to use a tile exchange? (y/n): ";
            std::cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                std::cout << "Enter the coordinates of the cell to change (x y): ";
                do {
                    std::cout << "X: ";
                    std::cin >> x;
                } while (x < 1 || x > game.getter_game_board().getter_board().size());
                do {
                    std::cout << "Y: ";
                    std::cin >> y;
                } while (y < 1 || y > game.getter_game_board().getter_board()[0].size());
                char &cell = game.getter_game_board().getter_case(x - 1, y - 1);
                if (cell == '.' || cell == 'P') {
                    cell = '0' + player.getter_id();
                    player.setter_tile_exchange(player.getter_tile_exchange() - 1);
                } else {
                    std::cout << "Invalid cell. You can only change empty cells or stones." << std::endl;
                }
            } else {
                break;
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




