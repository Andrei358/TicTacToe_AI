#include "model.hpp"

Model::Model()
{
    for(int row=0; row<BOARD_SIZE; ++row)
    {
        for(int column=0; column<BOARD_SIZE; ++column)
        {
            this->board[row][column]=Player::none;
        }
    }
}

void Model::do_move(Move_input move_input , Player player)
{
    this->board[move_input.row][move_input.column]=player;
}

bool Model::legal_move(Move_input move_input)
{
    if(move_input.row<0 || move_input.row>=BOARD_SIZE || move_input.column<0 || move_input.column>=BOARD_SIZE)
        return 0;
    else if(this->board[move_input.row][move_input.column]==Player::player1 || this->board[move_input.row][move_input.column]==Player::player2)
        return 0;
    else
        return 1;
}

Outcome Model::outcome()
{
    bool won;
    for(int row=0; row<BOARD_SIZE; ++row)
    {
        if(this->board[row][0]==Player::none)
            continue;

        won=1;
        for(int column=1; column<BOARD_SIZE; ++column)
        {
            if(this->board[row][column]!=this->board[row][0])
            {
                won=0;
                break;
            }
        }

        if(won)
            return (this->board[row][0]==Player::player1)? Outcome::win1 : Outcome::win2;
    }

    for(int column=0; column<BOARD_SIZE; ++column)
    {
        if(this->board[0][column]==Player::none)
            continue;

        won=1;
        for(int row=1; row<BOARD_SIZE; ++row)
        {
            if(this->board[row][column]!=this->board[0][column])
            {
                won=0;
                break;
            }
        }
        if(won)
            return (this->board[0][column]==Player::player1)? Outcome::win1 : Outcome::win2;
    }

    bool win=1;
    if(this->board[0][0]==Player::none)
            win=0;
    for(int diagonal=0; diagonal<BOARD_SIZE && win; ++diagonal)
    {
        if(this->board[diagonal][diagonal]!=this->board[0][0])
                win=0;
    }
    if(win)
        return (this->board[0][0]==Player::player1)? Outcome::win1 : Outcome::win2;

    win=1;
    if(this->board[0][BOARD_SIZE-1]==Player::none)
            win=0;
    for(int diagonal=0; diagonal<BOARD_SIZE && win; ++diagonal)
    {
        if(this->board[diagonal][BOARD_SIZE-diagonal-1]!=this->board[0][BOARD_SIZE-1])
                win=0;
    }
    if(win)
        return (this->board[BOARD_SIZE-1][0]==Player::player1)? Outcome::win1 : Outcome::win2;

    for(int row=0; row<BOARD_SIZE; ++row)
    {
        for(int column=0; column<BOARD_SIZE; ++column)
        {
            if(this->board[row][column]==Player::none)return Outcome::none;
        }
    }

    return Outcome::draw;
}

std::array<Player, BOARD_SIZE*BOARD_SIZE> Model::get_board(){
    std::array<Player, BOARD_SIZE*BOARD_SIZE> linear_board;
    int index=0;

    for(int row=0; row<BOARD_SIZE; ++row)
    {
        for(int column=0; column<BOARD_SIZE; ++column)
        {
            linear_board[index++]=this->board[row][column];
        }
    }

    return linear_board;
}

void Model::reset(){
    for(int row=0; row<BOARD_SIZE; ++row)
    {
        for(int column=0; column<BOARD_SIZE; ++column)
        {
            this->board[row][column]=Player::none;
        }
    }
}


