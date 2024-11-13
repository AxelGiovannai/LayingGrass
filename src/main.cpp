#include <iostream>
#include "../include/Game.h"
#include "../include/Board.h"
#include "../include/Player.h"
#include "../include/Tile.h"
#include "../include/CLI_renderer.h"

int main() {
    Game game;
    CLI_renderer::display_menu(game);
    CLI_renderer::refresh_terminal();
    CLI_renderer::display_game(game);
}

