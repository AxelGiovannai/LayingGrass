//
// Created by Axel on 04/11/2024.
//

#include "../include/Board.h"




std::vector<std::vector<char>> Board::getter_board() {
    return board;
}

char Board::getter_case(int x, int y) const {
    return board[x][y];
}


