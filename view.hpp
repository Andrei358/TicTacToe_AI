#ifndef viewTTT
#define viewTTT

#include <iostream>
#include <array>
#include <windows.h>
#include <string>
#include "common.hpp"
#define BOARD_SIZE 3

class View
{
    public:
        void output_board(std::array<Player, BOARD_SIZE*BOARD_SIZE>);
        void output_message(std::string);
        void output_outcome(Outcome);
        void wait(int miliseconds);
        void reset();
        Move_input get_move();
        std::string get_message();
};

#endif



