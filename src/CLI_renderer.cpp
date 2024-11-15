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

    std::cout << "  ";
    for (int col = 1; col <= board.getter_board()[0].size(); ++col) {
        if (col < 10) {
            std::cout << col << "  ";
        } else {
            std::cout << col << " ";
        }
    }
    std::cout << std::endl;

    char row_label = 'A';
    for (const auto &row : board.getter_board()) {
        std::cout << row_label++ << ' ';
        for (const auto &cell : row) {
            std::cout << cell << "  ";
        }
        std::cout << std::endl;
    }
}



void CLI_renderer::display_menu(Game &game) {
    int x = 0;
    std::cout << "Welcome to Laying Grass !" << std::endl;
    while (x < 1 || x > 9) {
        std::cout << "choose a number of player(1 to 9) : ";
        std::cin >> x;
    }

    game.setter_nb_players(x);
    for (int i = 0; i < x; ++i) {
        std::string name;
        do {
            std::cout << "Player " << i + 1 << " name : ";
            std::cin >> name;
        } while (name.empty() || name.length() > 20);
        game.setter_players(Player(name));
    }
    game.setter_game_board();
    }



void CLI_renderer::display_game(Game &game) {
    const int player_turn = game.getter_player_turn();
    if (player_turn < 0 || player_turn >= game.getter_nb_players()) {
        std::cerr << "Invalid player turn" << std::endl;
        return;
    }
    display_board(game);
    const Player current_player = game.getter_players(player_turn - 1);
    std::cout << "Player  :" << current_player.getter_name() << " turn" << std::endl;

    for (int i = 0; i < 3; ++i) {
        std::cout << "   "  << std::endl;
        const auto &tile_shape = current_player.getter_tiles_shape(i);
        for (const auto &row : tile_shape) {
            for (const auto &cell : row) {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        }
    }

    std::cout <<"| [P] Place | [R] Rotate | [F] Flip | [E] Exchange("<< current_player.getter_tile_exchange() <<") | [S] Stone | [V] Robbery |" << std::endl;
    char action;
    do {
        std::cout << "Invalid action" << std::endl;
        std::cin >> action;
    } while (action != 'P' && action != 'R' && action != 'F' && action != 'E' && action != 'S' && action != 'V');

    switch (action) {
        case 'P':
            //place
            break;
        case 'R':
            //rotate
            break;
        case 'F':
            //flip
            break;
        case 'E':
            //exchange
            break;
        case 'S':
            //stone
            break;
        case 'V':
            //robbery
            break;
        default:
            std::cout << "Invalid action" << std::endl;
            break;
    }
}


