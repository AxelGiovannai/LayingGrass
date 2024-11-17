#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>
#include "Tile.h"

class Player {
private:
    std::string name;
    std::string color; // Change char to std::string
    int id; // Add player ID
    int tile_exchange = 1;
    std::vector<std::vector<int>> starting_tile;
public:
    Player(std::string name, std::string color, int id); // Change char to std::string

    [[nodiscard]] std::string& getter_name();
    [[nodiscard]] std::string getter_color() const; // Change char to std::string
    [[nodiscard]] int getter_id() const;
    [[nodiscard]] int& getter_tile_exchange();
    [[nodiscard]] std::vector<std::vector<int>> getter_starting_tile() const;

    void setter_tile_exchange(int tile_exchange);
};

#endif //PLAYER_H