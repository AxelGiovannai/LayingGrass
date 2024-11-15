#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>
#include "Tile.h"

class Player {
private:
    std::string name;
    char color{}; // changer ca c'est de la merde séquences d’échappement ANSI
    int tile_exchange = 1;
    int stone = 0;
    int robbery = 0;
    std::vector<Tile> tiles;
public:
    explicit Player(const std::string& name);

    [[nodiscard]] std::string getter_name() const;
    void getter_color(); // changer ca c'est de la merde séquences d’échappement ANSI
    [[nodiscard]] int getter_tile_exchange() const;
    [[nodiscard]] int getter_stone() const;
    [[nodiscard]] int getter_robbery() const;
    [[nodiscard]] std::vector<std::vector<int>> getter_tiles_shape(int i) const;

    void setter_tile_exchange(int tile_exchange);
    void setter_stone(int stone);
    void setter_robbery(int robbery);
};

#endif //PLAYER_H