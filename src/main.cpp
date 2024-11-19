#include <iostream>
#include "../include/Game.h"
#include "../include/Board.h"
#include "../include/Player.h"
#include "../include/Tile.h"
#include "../include/CLI_renderer.h"

int main() {
    Game game;
    const int number_rounds = 9;
    CLI_renderer::display_menu(game);
    CLI_renderer::first_turn(game);
    while (game.getter_nb_rounds() < number_rounds) {
        CLI_renderer::refresh_terminal();
        CLI_renderer::display_game(game);
        game.apply_bonus_effects();
        game.setter_player_turn();
    }
    CLI_renderer::refresh_terminal();
    CLI_renderer::display_board(game);
    Game::use_final_exchange(game);
    game.victory(game);
    return 0;
}

