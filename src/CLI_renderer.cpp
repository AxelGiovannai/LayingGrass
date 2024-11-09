//
// Created by Axel on 08/11/2024.
//

#include "../include/CLI_renderer.h"
#include <iostream>
#include <vector>
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

