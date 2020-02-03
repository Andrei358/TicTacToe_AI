#pragma once

#include <array>

#define BOARD_SIZE 3
#define LEAF_VALUE BOARD_SIZE*BOARD_SIZE+1

enum class Player
{
    none='_',
    player1='X',
    player2='O'
};

enum class Outcome
{
    none=-1,
    win1='X',
    win2='O',
    draw=0
};

struct Move_input{
    int row,column;
};

