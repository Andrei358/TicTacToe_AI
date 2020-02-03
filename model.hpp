#ifndef modelTTT
#define modelTTT

#include <array>
#include "common.hpp"
#define BOARD_SIZE 3

class Model
{
    private:
        Player board[BOARD_SIZE][BOARD_SIZE];
    public:
        Model();
        void do_move(Move_input, Player);
        bool legal_move(Move_input);
        Outcome outcome();
        std::array<Player, BOARD_SIZE*BOARD_SIZE> get_board();
        void reset();
};

#endif



