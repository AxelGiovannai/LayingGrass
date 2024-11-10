//
// Created by Axel on 08/11/2024.
//

#include "../include/CLI_renderer.h"
#include <iostream>
#include <vector>
#include <string.h>
#include <cstdlib>


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

    char row_label = 'A';
    for (const auto &row : board.getter_board()) {
        std::cout << row_label++ << ' ';
        for (const auto &cell : row) {
            std::cout << cell << "  ";
        }
        std::cout << std::endl;
    }
}

void CLI_renderer::refresh_terminal() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void CLI_renderer::display_menu(Game &game) {
    int  x;
    std::cout << "Welcome to Laying Grass !" << std::endl;
    while (x < 1 || x > 9) {
        std::cout << "choose a number of player(1 to 9) : "; std::cin >> x;
    }

    game.setter_nb_players(x);
    for (int i = 0; i < x; ++i) {
        char name[20]="";

        while (strlen(name) == 0 || strlen(name) > 20 || name[0] == ' ') {
            std::cout << "Player " << i + 1 << " name : "; std::cin >> name;
        }
        game.setter_players(Player(name));
    }
}

void CLI_renderer::display_game(Game &game) {

}


