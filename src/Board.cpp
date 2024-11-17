//
// Created by Axel on 04/11/2024.
//

#include "../include/Board.h"




std::vector<std::vector<char>>& Board::getter_board() {
    return board;
}

char& Board::getter_case(int x, int y){
    return board[x][y];
}

void Board::setter_board(const int x, const int y) {
    board.clear(); // Clear any existing data
    board.resize(x, std::vector<char>(y, '.')); // Resize and initialize with '.'
}

void Board::setter_case(const int x, const int y, const char c) {
    board[x][y] = c;
}


bool Board::place_tile(const std::vector<std::vector<int>> &tile, int x, int y, char player_id) {
    for (int i = 0; i < tile.size(); ++i) {
        for (int j = 0; j < tile[i].size(); ++j) {
            if (tile[i][j] == 1) {
                if (board[x + i][y + j] != '.') {
                    return false; // Tile cannot be placed
                }
            }
        }
    }
    for (int i = 0; i < tile.size(); ++i) {
        for (int j = 0; j < tile[i].size(); ++j) {
            if (tile[i][j] == 1) {
                board[x + i][y + j] = '0' + player_id;
            }
        }
    }
    return true;
}