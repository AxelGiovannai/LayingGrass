#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>
#include "Tile.h"

class Player {
private:
    std::string name;
    char color;
    int id; // Add player ID
    int tile_exchange = 1;
    std::vector<std::vector<int>> starting_tile;
public:
    Player(std::string name, char color, int id);

    [[nodiscard]] std::string& getter_name();
    [[nodiscard]] char getter_color() const;
    [[nodiscard]] int getter_id() const;
    [[nodiscard]] int& getter_tile_exchange();
    [[nodiscard]] std::vector<std::vector<int>> getter_starting_tile() const;

    void setter_tile_exchange(int tile_exchange);
};

#endif //PLAYER_H