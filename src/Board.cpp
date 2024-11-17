//
// Created by Axel on 04/11/2024.
//

#include "../include/Board.h"
#include "../include/Game.h"
#include <unordered_map>


std::vector<std::vector<char>>& Board::getter_board() {
    return board;
}

char& Board::getter_case(int x, int y){
    return board[x][y];
}

void Board::setter_board(const int x, const int y) {
    board.clear();
    board.resize(x, std::vector<char>(y, '.'));
}

void Board::setter_case(const int x, const int y, const char c) {
    board[x][y] = c;
}

std::string Board::get_color_code(char player_id) {
    static std::unordered_map<char, std::string> color_map = {
        {'1', "\033[31m"}, // Red
        {'2', "\033[32m"}, // Green
        {'3', "\033[34m"}, // Blue
        {'4', "\033[33m"}, // Yellow
        {'5', "\033[35m"}, // Magenta
        {'6', "\033[36m"}, // Cyan
        {'7', "\033[93m"}, // Bright Yellow
        {'8', "\033[91m"}, // Bright Red
        {'9', "\033[92m"}, // Bright Green
        {'P', "\033[96m"}, // Bright Cyan for stones
        {'E', "\033[96m"}, // Bright Cyan for tile exchanges
        {'V', "\033[96m"}  // Bright Cyan for robberies
    };
    return color_map[player_id];
}



bool Board::can_place_tile(const std::vector<std::vector<int>> &tile, int x, int y, char player_id) {
    if (x < 0 || y < 0 || x + tile.size() > board.size() || y + tile[0].size() > board[0].size()) {
        return false;
    }

    bool adjacent_to_player_tile = false;

    for (int i = 0; i < tile.size(); ++i) {
        for (int j = 0; j < tile[i].size(); ++j) {
            if (tile[i][j] == 1) {
                if (board[x + i][y + j] != '.') {
                    return false;
                }

                if ((x + i > 0 && board[x + i - 1][y + j] == '0' + player_id) ||
                    (x + i < board.size() - 1 && board[x + i + 1][y + j] == '0' + player_id) ||
                    (y + j > 0 && board[x + i][y + j - 1] == '0' + player_id) ||
                    (y + j < board[0].size() - 1 && board[x + i][y + j + 1] == '0' + player_id)) {
                    adjacent_to_player_tile = true;
                }
            }
        }
    }

    return adjacent_to_player_tile;
}

bool Board::place_tile(const std::vector<std::vector<int>> &tile, int x, int y, char player_id) {
    if (!can_place_tile(tile, x, y, player_id)) {
        return false;
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

bool Board::place_first_tile(const std::vector<std::vector<int>> &tile, int x, int y, char player_id) {
    for (int i = 0; i < tile.size(); ++i) {
        for (int j = 0; j < tile[i].size(); ++j) {
            if (tile[i][j] == 1) {
                if (board[x + i][y + j] != '.') {
                    return false;
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