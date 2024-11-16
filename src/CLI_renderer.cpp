//
// Created by Axel on 08/11/2024.
//

#include "../include/CLI_renderer.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>


void CLI_renderer::refresh_terminal() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void CLI_renderer::display_board(Game &game) {

    Board board = game.getter_game_board();


    std::cout << "   ";
    for (int col = 1; col <= board.getter_board()[0].size(); ++col) {
        if (col < 10) {
            std::cout << col << "  ";
        } else {
            std::cout << col << " ";
        }
    }
    std::cout << std::endl;


    int row_number = 1;
    for (const auto &row : board.getter_board()) {
        if (row_number < 10) {
            std::cout << " " << row_number << ' ';
        } else {
            std::cout << row_number << ' ';
        }
        for (const auto &cell : row) {
            std::cout << cell << "  ";
        }
        std::cout << std::endl;
        ++row_number;
    }
}



void CLI_renderer::display_menu(Game &game) {
    int x = 0;
    std::cout << "Welcome to Laying Grass!" << std::endl;
    while (x < 1 || x > 9) {
        std::cout << "Choose a number of players (1 to 9): ";
        std::cin >> x;
    }
    game.setter_nb_players(x);
    const std::vector<char> colors = {'R', 'G', 'B', 'Y', 'M', 'C', 'W', 'O', 'P'}; // Predefined list of colors
    for (int i = 0; i < x; ++i) {
        std::string name;
        std::cout << "Player " << i + 1 << " name: ";
        std::cin >> name;
        game.setter_players(Player(name, colors[i]));
    }
    game.setter_game_board();
    Game::generate_tile(game);
}



void CLI_renderer::display_game(Game &game) {
    const int player_turn = game.getter_player_turn();
    if (player_turn < 0 || player_turn >= game.getter_nb_players()) {
        std::cerr << "Invalid player turn" << std::endl;
        return;
    }

    display_board(game);
    Player current_player = game.getter_players(player_turn - 1);
    const std::string player_name = current_player.getter_name();
    std::cout << "Player turn :" << player_name << std::endl;

    std::cout << "playable Tile : " << std::endl;
    for (const auto tile_shape = game.getter_tiles(0).getter_shape(); const auto &row : tile_shape) {
        for (const auto &cell : row) {
            if (cell == 1) {
                std::cout << "1 ";
            } else {
                std::cout << cell << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Current Tile : " << std::endl;
    size_t max_height = 0;
    for (int i = 1; i < 6; ++i) {
        max_height = std::max(max_height, game.getter_tiles(i).getter_shape().size());
    }

    // Display the tiles horizontally
    for (size_t row = 0; row < max_height; ++row) {
        for (int i = 1; i < 6; ++i) {
            const auto &tile_shape = game.getter_tiles(i).getter_shape();
            if (row < tile_shape.size()) {
                for (const auto &cell : tile_shape[row]) {
                    std::cout << cell << " ";
                }
            } else {
                for (size_t col = 0; col < tile_shape[0].size(); ++col) {
                    std::cout << "  ";
                }
            }
            std::cout << " "; // Space between tiles
        }
        std::cout << std::endl;
    }

        std::cout << std::endl;
        std::cout <<"| [P] Place | [R] Rotate | [F] Flip | [E] Exchange("<< current_player.getter_tile_exchange() <<") |" << std::endl;
        char action;
        do {
            std::cout << "Choice :" << std::endl;
            std::cin >> action;
        } while (action != 'P' && action != 'R' && action != 'F' && action != 'E' && action != 'S' && action != 'V' && action != 'Q');

        switch (action) {
            case 'P':
                int x, y;
                do {
                    std::cout << "X :" << std::endl;
                    std::cin >> x;
                } while (x < 1 || x > game.getter_game_board().getter_board().size());
                do {
                    std::cout << "Y :" << std::endl;
                    std::cin >> y;
                } while (y < 1 || y > game.getter_game_board().getter_board()[0].size());
                game.getter_game_board().place_tile(game.getter_tiles(0).getter_shape(), x - 1, y - 1, current_player.getter_color());
                    break;
            case 'R':
                game.getter_tiles(0).rotate();
                refresh_terminal();
                display_game(game);
                    break;
            case 'F':
            game.getter_tiles(0).flip();
            refresh_terminal();
            display_game(game);
                    break;
            case 'E':
                //exchange
                    break;
            case 'Q':
                exit(0);
                    break;
            default:
                std::cout << "Invalid action" << std::endl;
            break;
        }
    }

