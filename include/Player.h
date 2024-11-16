#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>
#include "Tile.h"

class Player {
private:
    std::string name;
    char color;
    int tile_exchange = 1;
    int stone = 0;
    int robbery = 0;
    std::vector<std::vector<int>> starting_tile = {{1}}; // 1x1 starting tile
public:
    Player(const std::string& name, char color);

    [[nodiscard]] std::string getter_name() const;
    [[nodiscard]] char getter_color() const;
    [[nodiscard]] int getter_tile_exchange() const;
    [[nodiscard]] int getter_stone() const;
    [[nodiscard]] int getter_robbery() const;
    [[nodiscard]] std::vector<std::vector<int>> getter_starting_tile() const;
    void setter_tile_exchange(int tile_exchange);
    void setter_stone(int stone);
    void setter_robbery(int robbery);
};

#endif //PLAYER_H