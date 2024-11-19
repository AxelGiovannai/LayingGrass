//
// Created by Axel on 08/11/2024.
//

#include "../include/CLI_renderer.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <limits>


void CLI_renderer::refresh_terminal() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void CLI_renderer::display_board(Game &game) {
    Board &board = game.getter_game_board();
    std::cout << "   ";
    for (int col = 1; col <= board.getter_board()[0].size(); ++col) {
        if (col < 10) {
            std::cout << col << "  ";
        } else {
            std::cout << col << " ";
        }
    }
    std::cout << std::endl;

    int row_number = 1;
    for (const auto &row : board.getter_board()) {
        if (row_number < 10) {
            std::cout << " " << row_number << ' ';
        } else {
            std::cout << row_number << ' ';
        }
        for (const auto &cell : row) {
            if (cell != '.') {
                std::cout << board.get_color_code(cell) << cell << "\033[0m" << "  ";
            } else {
                std::cout << cell << "  ";
            }
        }
        std::cout << std::endl;
        ++row_number;
    }
}



void CLI_renderer::display_menu(Game &game) {
    int x = 0;
    std::cout << "Welcome to Laying Grass!" << std::endl;
    while (x < 2 || x > 9) {
        std::cout << "Choose a number of players (2 to 9): ";
        std::cin >> x;
    }
    game.setter_nb_players(x);
    const std::vector<std::string> colors = {
        "\033[31m", // Red
        "\033[32m", // Green
        "\033[34m", // Blue
        "\033[33m", // Yellow
        "\033[35m", // Magenta
        "\033[36m", // Cyan
        "\033[93m", // Bright Yellow
        "\033[91m", // Bright Red
        "\033[92m"  // Bright Green
    };
    for (int i = 0; i < x; ++i) {
        std::string name;
        std::cout << "Player " << i + 1 << " name: ";
        std::cin >> name;
        game.setter_players(Player(name, colors[i], i + 1));
    }
    game.setter_game_board();
    Game::generate_tile(game);
}


void CLI_renderer::display_game(Game &game) {
    const int player_turn = game.getter_player_turn();
    if (player_turn < 1 || player_turn > game.getter_nb_players()) {
        std::cerr << "Invalid player turn" << std::endl;
        return;
    }

    const std::string RESET = "\033[0m";

    Player current_player = game.getter_players(player_turn - 1);
    const std::string player_name = current_player.getter_name();
    const std::string player_color = current_player.getter_color();
    std::cout << player_color << "Player " << current_player.getter_id() << " (" << player_name << ") - Round " << game.getter_nb_rounds() + 1 << RESET << std::endl;
    std::cout << " " << std::endl;
    display_board(game);

    std::cout << " " << std::endl;
    std::cout << "Playable Tile: " << std::endl;
    for (const auto tile_shape = game.getter_tiles(0).getter_shape(); const auto &row : tile_shape) {
        for (const auto &cell : row) {
            if (cell == 1) {
                std::cout << "1 ";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << " " << std::endl;
    std::cout << "Current Tile: " << std::endl;
    size_t max_height = 0;
    for (int i = 1; i < 6; ++i) {
        max_height = std::max(max_height, game.getter_tiles(i).getter_shape().size());
    }


    for (size_t row = 0; row < max_height; ++row) {
        for (int i = 1; i < 6; ++i) {
            const auto &tile_shape = game.getter_tiles(i).getter_shape();
            if (row < tile_shape.size()) {
                for (const auto &cell : tile_shape[row]) {
                    if (cell == 1) {
                        std::cout << "1 ";
                    } else {
                        std::cout << "  ";
                    }
                }
            } else {
                for (size_t col = 0; col < tile_shape[0].size(); ++col) {
                    std::cout << "  ";
                }
            }
            if (i < 5) {
                std::cout << "  |  ";
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "[P] Place | [R] Rotate | [F] Flip | [E] Exchange Coupon (" << current_player.getter_tile_exchange() << ") " << "| (Q) Quit" << std::endl;
    char action;
    do {
        std::cout << "Choice: ";
        action = _getch();
        std::cout << action << std::endl;
    } while (action != 'P' && action != 'R' && action != 'F' && action != 'E' && action != 'S' && action != 'V' && action != 'Q' && action != 'p' && action != 'r' && action != 'f' && action != 'e' && action != 's' && action != 'v' && action != 'q');

    switch (action) {
        case 'p':
        case 'P': {
            bool valid_placement = false;
            while (!valid_placement) {
                std::cout << "Coordinates of the most top-left '1' in the tile:" << std::endl;
                int x, y;
                while (true) {
                    std::cout << "X: ";
                    std::cin >> x;
                    if (std::cin.fail()) {
                        std::cin.clear(); // Clear the error state
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input. Please enter a number." << std::endl;
                    } else if (x < 1 || x > game.getter_game_board().getter_board().size()) {
                        std::cout << "Invalid coordinate. Please enter a number between 1 and " << game.getter_game_board().getter_board().size() << "." << std::endl;
                    } else {
                        break;
                    }
                }
                while (true) {
                    std::cout << "Y: ";
                    std::cin >> y;
                    if (std::cin.fail()) {
                        std::cin.clear(); // Clear the error state
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input. Please enter a number." << std::endl;
                    } else if (y < 1 || y > game.getter_game_board().getter_board()[0].size()) {
                        std::cout << "Invalid coordinate. Please enter a number between 1 and " << game.getter_game_board().getter_board()[0].size() << "." << std::endl;
                    } else {
                        break;
                    }
                }
                if (game.getter_game_board().can_place_tile(game.getter_tiles(0).getter_shape(), y - 1, x - 1, static_cast<char>(current_player.getter_id()))) {
                    game.getter_game_board().place_tile(game.getter_tiles(0).getter_shape(), y - 1, x - 1, static_cast<char>(current_player.getter_id()));
                    game.remove_tile(0);
                    valid_placement = true;
                } else {
                    std::cout << "Invalid placement. Try again." << std::endl;
                }
            }
            break;
        }
        case 'r':
        case 'R':
            game.getter_tiles(0).rotate();
            refresh_terminal();
            display_game(game);
            break;
        case 'f':
        case 'F':
            game.getter_tiles(0).flip();
            refresh_terminal();
            display_game(game);
            break;
        case 'e':
        case 'E': {
            std::cout << "[E] Exchange Tile | [R] Remove Pierre | [Q] Return " << std::endl;
            char exchange_action;
            do {
                std::cout << "Choice: ";
                exchange_action = _getch();
                std::cout << exchange_action << std::endl;
            } while (exchange_action != 'E' && exchange_action != 'R' && exchange_action != 'e' && exchange_action != 'r' && exchange_action != 'Q' && exchange_action != 'q');
            switch (exchange_action) {
                case 'r':
                case 'R':
                    int x, y;
                    while (true) {
                        std::cout << "X: ";
                        std::cin >> x;
                        if (std::cin.fail()) {
                            std::cin.clear(); // Clear the error state
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Invalid input. Please enter a number." << std::endl;
                        } else if (x < 1 || x > game.getter_game_board().getter_board().size()) {
                            std::cout << "Invalid coordinate. Please enter a number between 1 and " << game.getter_game_board().getter_board().size() << "." << std::endl;
                        } else {
                            break;
                        }
                    }
                    while (true) {
                        std::cout << "Y: ";
                        std::cin >> y;
                        if (std::cin.fail()) {
                            std::cin.clear(); // Clear the error state
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Invalid input. Please enter a number." << std::endl;
                        } else if (y < 1 || y > game.getter_game_board().getter_board()[0].size()) {
                            std::cout << "Invalid coordinate. Please enter a number between 1 and " << game.getter_game_board().getter_board()[0].size() << "." << std::endl;
                        } else {
                            break;
                        }
                    }
                    if (game.getter_game_board().getter_board()[y - 1][x - 1] == 'P') {
                        game.remove_rock(game, y - 1, x - 1);
                    } else {
                        refresh_terminal();
                        display_game(game);
                    }
                    refresh_terminal();
                    display_game(game);
                    break;
                case 'e':
                case 'E':
                    int tile_index;
                    std::cout << "Enter the index of the tile to exchange: ";
                    std::cin >> tile_index;
                    if (tile_index > 0 && tile_index < 6) {
                        game.use_tile_exchange(tile_index);
                    } else {
                        std::cout << "Invalid tile index" << std::endl;
                    }
                    refresh_terminal();
                    display_game(game);
                    break;
                case 'q':
                case 'Q':
                    refresh_terminal();
                    display_game(game);
                    break;
            }
            refresh_terminal();
            display_game(game);
            break;

        }
        case 'q':
        case 'Q':
            exit(0);
            break;
        default:
            std::cout << "Invalid action" << std::endl;
            break;
    }
}
void CLI_renderer::first_turn(Game &game) {
    refresh_terminal();

    for (int i = 0; i < game.getter_nb_players(); ++i) {
        Player &player = game.getter_players(i);
        const std::string RESET = "\033[0m";
        const std::string player_name = player.getter_name();
        const std::string player_color = player.getter_color();
        std::cout << player_color << "Player " << player.getter_id() << " (" << player_name << ") - Placing first tile" << RESET << std::endl;
        std::cout << std::endl;
        display_board(game);
        std::cout << "Enter the coordinates of your first tile:" << std::endl;
        int x, y;
        while (true) {
            std::cout << "X: ";
            std::cin >> x;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number." << std::endl;
            } else if (x < 1 || x > game.getter_game_board().getter_board().size()) {
                std::cout << "Invalid coordinate. Please enter a number between 1 and " << game.getter_game_board().getter_board().size() << "." << std::endl;
            } else {
                break;
            }
        }
        while (true) {
            std::cout << "Y: ";
            std::cin >> y;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number." << std::endl;
            } else if (y < 1 || y > game.getter_game_board().getter_board()[0].size()) {
                std::cout << "Invalid coordinate. Please enter a number between 1 and " << game.getter_game_board().getter_board()[0].size() << "." << std::endl;
            } else {
                break;
            }
        }
        if (game.getter_game_board().place_first_tile(player.getter_starting_tile(), y - 1, x - 1, static_cast<char>(player.getter_id()))) {
            refresh_terminal();
        } else {
            std::cout << "Invalid placement. Try again." << std::endl;
            refresh_terminal();
            --i;
        }
    }
}