#ifndef minimaxALGO
#define minimaxALGO

#include <limits>
#include "common.hpp"

class Minimax{
    private:
        Player board[BOARD_SIZE][BOARD_SIZE];
        bool legal_move(Move_input);
        Outcome  outcome();
        std::pair<int, Move_input> maxsearch(Player, int, int, int);
        std::pair<int, Move_input> minsearch(Player, int, int, int);
    public:
        Move_input computer_move(std::array<Player, BOARD_SIZE*BOARD_SIZE>, Player);
};

#endif
