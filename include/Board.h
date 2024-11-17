//
// Created by Axel on 04/11/2024.
//

#ifndef BOARD_H
#define BOARD_H
#include <vector>


class Board {
private:
    std::vector<std::vector<char>> board;
public:
    std::vector<std::vector<char>>& getter_board();
    [[nodiscard]] char& getter_case(int x, int y);
    void setter_board(int x, int y);
    void setter_case(int x, int y, char c);
    bool place_tile(const std::vector<std::vector<int>> &tile, int x, int y, char player_id);
    bool place_first_tile(const std::vector<std::vector<int>> &tile, int x, int y, char player_id);
    bool can_place_tile(const std::vector<std::vector<int>> &tile, int x, int y, char player_id);
};



#endif //BOARD_H
