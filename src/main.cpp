#include <iostream>
#include "../include/Game.h"
#include "../include/Board.h"
#include "../include/Player.h"
#include "../include/Tile.h"
#include "../include/CLI_renderer.h"

int main() {
    Game game;
    const int number_rounds = 10;
    CLI_renderer::display_menu(game);
    CLI_renderer::first_turn(game);
    while (game.getter_nb_rounds() < number_rounds) {
        CLI_renderer::refresh_terminal();
        CLI_renderer::display_game(game);
        game.setter_player_turn();
    }
    std::cout << "PROUT FINI ! :p" << std::endl;
    return 0;
}

