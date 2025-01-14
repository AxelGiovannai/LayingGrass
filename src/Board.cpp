//
// Created by Axel on 04/11/2024.
//

#include "../include/Board.h"
#include "../include/Game.h"
#include <unordered_map>
#include <iostream>

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
        {'1', "\033[31m"},
        {'2', "\033[32m"},
        {'3', "\033[34m"},
        {'4', "\033[33m"},
        {'5', "\033[35m"},
        {'6', "\033[36m"},
        {'7', "\033[93m"},
        {'8', "\033[91m"},
        {'9', "\033[92m"},
        {'P', "\033[96m"},
        {'E', "\033[96m"},
        {'V', "\033[96m"}
    };
    return color_map[player_id];
}



bool Board::can_place_tile(const std::vector<std::vector<int>> &tile, int x, int y, char player_id) {
    bool adjacent_to_player_tile = false;
    int top_left_x = -1, top_left_y = -1;

    // Find the top-left 1 in the tile
    for (int i = 0; i < tile.size(); ++i) {
        for (int j = 0; j < tile[i].size(); ++j) {
            if (tile[i][j] == 1) {
                top_left_x = i;
                top_left_y = j;
                break;
            }
        }
        if (top_left_x != -1) break;
    }

    if (top_left_x == -1 || top_left_y == -1) return false;

    int tile_height = tile.size();
    int tile_width = tile[0].size();
    if (x < 0 || y < 0 || x + tile_height > board.size() + 1 || y + tile_width > board[0].size() + 1) {
        return false;
    }

    for (int i = 0; i < tile.size(); ++i) {
        for (int j = 0; j < tile[i].size(); ++j) {
            if (tile[i][j] == 1) {
                int board_x = x + (i - top_left_x);
                int board_y = y + (j - top_left_y);

                if (board[board_x][board_y] != '.') {
                    return false;
                }

                if ((board_x > 0 && board[board_x - 1][board_y] == '0' + player_id) ||
                    (board_x < board.size() - 1 && board[board_x + 1][board_y] == '0' + player_id) ||
                    (board_y > 0 && board[board_x][board_y - 1] == '0' + player_id) ||
                    (board_y < board[0].size() - 1 && board[board_x][board_y + 1] == '0' + player_id)) {
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

    int top_left_x = -1, top_left_y = -1;


    for (int i = 0; i < tile.size(); ++i) {
        for (int j = 0; j < tile[i].size(); ++j) {
            if (tile[i][j] == 1) {
                top_left_x = i;
                top_left_y = j;
                break;
            }
        }
        if (top_left_x != -1) break;
    }

    for (int i = 0; i < tile.size(); ++i) {
        for (int j = 0; j < tile[i].size(); ++j) {
            if (tile[i][j] == 1) {
                int board_x = x + (i - top_left_x);
                int board_y = y + (j - top_left_y);

                if (board_x >= 0 && board_y >= 0 && board_x < board.size() && board_y < board[0].size()) {
                    board[board_x][board_y] = '0' + player_id;
                }
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


