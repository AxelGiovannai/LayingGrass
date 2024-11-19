# Documentation Technique

## Vue d'ensemble

Ce projet est un jeu de plateau en C++ où les joueurs placent des tuiles sur un plateau pour couvrir le plus de cases possible. Le jeu utilise une interface en ligne de commande (CLI) pour afficher le plateau et interagir avec les joueurs.

## Classes et Méthodes

### Game

- **Attributs** :
    - `nb_players` : Nombre de joueurs.
    - `player_turn` : Tour actuel du joueur.
    - `nb_rounds` : Nombre de tours joués.
    - `game_board` : Plateau de jeu.
    - `players` : Liste des joueurs.
    - `tiles` : Liste des tuiles disponibles.

- **Méthodes** :
    - `getter_nb_players()`, `getter_player_turn()`, `getter_nb_rounds()`, `getter_game_board()`, `getter_players(int i)`, `getter_tiles(int i)` : Méthodes pour obtenir les attributs.
    - `setter_nb_players(int nb)`, `setter_player_turn()`, `setter_nb_rounds()`, `setter_game_board()`, `setter_players(const Player& player)`, `setter_tiles(const Tile& tile)` : Méthodes pour définir les attributs.
    - `initialize_game()`, `place_initial_stones()`, `place_initial_tile_exchanges()`, `place_initial_robberies()`, `remove_tile(int index)`, `use_tile_exchange(int tile_index)`, `remove_rock(Game &game, int x, int y)`, `apply_bonus_effects()`, `largest_square_covered(char player_id)`, `count_grass_squares(char player_id)`, `victory(Game &game)`, `use_final_exchange(Game &game)`, `generate_tile(Game &game)` : Méthodes pour gérer le jeu.

### Board

- **Attributs** :
    - `board` : Représentation du plateau de jeu sous forme de matrice de caractères.

- **Méthodes** :
    - `getter_board()`, `getter_case(int x, int y)` : Méthodes pour obtenir les cases du plateau.
    - `setter_board(int x, int y)`, `setter_case(int x, int y, char c)` : Méthodes pour définir les cases du plateau.
    - `place_tile(const std::vector<std::vector<int>> &tile, int x, int y, char player_id)`, `place_first_tile(const std::vector<std::vector<int>> &tile, int x, int y, char player_id)`, `can_place_tile(const std::vector<std::vector<int>> &tile, int x, int y, char player_id)` : Méthodes pour placer des tuiles sur le plateau.
    - `get_color_code(char player_id)` : Méthode pour obtenir le code couleur d'un joueur.

### Player

- **Attributs** :
    - `name` : Nom du joueur.
    - `color` : Couleur du joueur.
    - `id` : Identifiant du joueur.
    - `tile_exchange` : Nombre d'échanges de tuiles disponibles.
    - `starting_tile` : Tuile de départ du joueur.

- **Méthodes** :
    - `getter_name()`, `getter_color()`, `getter_id()`, `getter_tile_exchange()`, `getter_starting_tile()` : Méthodes pour obtenir les attributs.
    - `setter_tile_exchange(int tile_exchange)`, `increase_tile_exchange()` : Méthodes pour définir et augmenter le nombre d'échanges de tuiles.

### Tile

- **Attributs** :
    - `shape` : Forme de la tuile sous forme de matrice d'entiers.

- **Méthodes** :
    - `getter_shape()`, `setter_shape(const std::vector<std::vector<int>> &shape)` : Méthodes pour obtenir et définir la forme de la tuile.
    - `rotate()`, `flip()` : Méthodes pour faire pivoter et retourner la tuile.

### CLI_renderer

- **Méthodes** :
    - `display_board(Game &game)`, `refresh_terminal()`, `display_menu(Game &game)`, `display_game(Game &game)`, `first_turn(Game &game)` : Méthodes pour afficher le plateau, rafraîchir le terminal, afficher le menu, afficher le jeu et gérer le premier tour.

## Conclusion

Cette documentation fournit une vue d'ensemble des choix d'implémentation et des détails pour le projet de jeu. Chaque classe et méthode est conçue pour gérer des aspects spécifiques du jeu, assurant ainsi une base de code modulaire et maintenable.