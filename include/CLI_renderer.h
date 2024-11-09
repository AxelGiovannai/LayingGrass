//
// Created by Axel on 08/11/2024.
//

#ifndef CLI_RENDERER_H
#define CLI_RENDERER_H
#include "Game.h"


class CLI_renderer {
public:
    static void display_board(Game &game);
    static void refresh_terminal();
    
};



#endif //CLI_RENDERER_H
