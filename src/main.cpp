#include <iostream>
#include "../include/Game.h"
#include "../include/Board.h"
#include "../include/Player.h"
#include "../include/Tile.h"
#include "../include/CLI_renderer.h"

int main() {
    Game game;
    CLI_renderer::display_menu(game);
    std::cout << "before refresh "  << std::endl;
    CLI_renderer::refresh_terminal();
    std::cout << "after refresh "  << std::endl;
    CLI_renderer::display_game(game);
    return 0;
}

