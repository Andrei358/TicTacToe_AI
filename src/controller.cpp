#include "controller.hpp"

bool Controller::player_interaction(Player player){
    Move_input move_input;
    Outcome outcome;

    this->view.reset();
    this->view.output_board(this->model.get_board());
    std::string player_string(1, (char)player);
    this->view.output_message(player_string);
    this->view.output_message(" moves:\n");

    if (player == Player::player1)
        move_input = this->view.get_move();
    else{
        move_input = this->computer.computer_move(this->model.get_board(), Player::player2);
        this->view.wait(500);
    }

    while(!this->model.legal_move(move_input))
    {
        this->view.output_message("illegal move!\n");
        move_input=this->view.get_move();
    }

    this->model.do_move(move_input, player);
    outcome = this->model.outcome();
    if(outcome != Outcome::none)
    {
        this->view.reset();
        this->view.output_board(this->model.get_board());
        this->view.output_outcome(outcome);
        return 0;
    }
    return 1;
}

void Controller::single_game(){
    this->model.reset();
    bool game_on = 1;
    while(game_on){
        if(!this->player_interaction(Player::player1))
            return;
        if(!this->player_interaction(Player::player2))
            return;
    }
}

void Controller::start_game(){
    std::string repeat;
    this->view.output_message("Welcome to Tic-Tac-Toe!\n");
    this->view.wait(1000);
    do{
        this->single_game();
        this->view.output_message("Do you want to play again? (Y/N)\n");
        repeat=this->view.get_message();
    }while(repeat=="Y" || repeat=="y" || repeat=="yes");
}

