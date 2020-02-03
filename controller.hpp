#ifndef controllerTTT
#define controllerTTT

#include <iostream>
#include <array>
#include <string>
#include "common.hpp"
#include "model.hpp"
#include "view.hpp"
#include "minimax.hpp"
#define BOARD_SIZE 3

class Controller
{
    private:
        Model model;
        View view;
        Minimax computer;
        bool player_interaction(Player);
        void single_game();
    public:
        void start_game();
};

#endif


