//
// Created by Axel on 04/11/2024.
//

#include "../include/Board.h"




std::vector<std::vector<char>> Board::getter_board() {
    return board;
}

char Board::getter_case(const int x, const int y) const {
    return board[x][y];
}

void Board::setter_board(const int x, const int y) {
    board.resize(x);
    for (int i = 0; i < x; ++i) {
        board[i].resize(y, '.');
    }
}

void Board::setter_case(const int x, const int y, const char c) {
    board[x][y] = c;
}


