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
public:
    Player(std::string  name, char color);

    [[nodiscard]] std::string& getter_name();
    [[nodiscard]] char getter_color() const;
    [[nodiscard]] int& getter_tile_exchange();

    void setter_tile_exchange(int tile_exchange);
};

#endif //PLAYER_H