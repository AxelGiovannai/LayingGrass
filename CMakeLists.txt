cmake_minimum_required(VERSION 3.29)
project(LayingGrass)

set(CMAKE_CXX_STANDARD 26)

add_executable(LayingGrass src/main.cpp
        src/Tiles.cpp
        include/Tiles.h
        src/Game.cpp
        include/Game.h
        src/Player.cpp
        include/Player.h
        src/Board.cpp
        include/Board.h)
