#include "view.hpp"

void View::output_board(std::array<Player, BOARD_SIZE*BOARD_SIZE> board){
    int index=0;
    for(int row=0; row<BOARD_SIZE; ++row)
    {
        for(int column=0; column<BOARD_SIZE; ++column)
        {
            std::cout<<(char)board[index++]<<' ';
        }
        std::cout<<'\n';
    }
}

void View::output_message(std::string message){
    std::cout<<message;
}

void View::output_outcome(Outcome outcome){
    if(outcome==Outcome::win1 || outcome==Outcome::win2)
        std::cout<<(char)outcome<<" wins!\n";
    else if(outcome==Outcome::draw)
        std::cout<<"It's a draw!\n";
}

void View::wait(int miliseconds){
    Sleep(miliseconds);
}

void View::reset(){
    system("cls");
}

Move_input View::get_move(){
    Move_input player_move;
    int input;
    std::cin>>input;
    player_move={input/10-1,input%10-1};
    return player_move;
}

std::string View::get_message(){
    std::string string_input;
    std::cin>>string_input;
    return string_input;
}
