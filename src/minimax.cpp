#include "minimax.hpp"

bool Minimax::legal_move(Move_input move_input)
{
    if(move_input.row<0 || move_input.row>=BOARD_SIZE || move_input.column<0 || move_input.column>=BOARD_SIZE)
        return 0;
    else if(this->board[move_input.row][move_input.column]==Player::player1 || this->board[move_input.row][move_input.column]==Player::player2)
        return 0;
    else
        return 1;
}

Outcome Minimax::outcome()
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

std::pair<int, Move_input> Minimax::minsearch(Player player, int depth, int alpha, int beta)
{
    int minimum = std::numeric_limits<int>::max();
    std::pair<int, Move_input> return_value, temp;
    Player opposite_player = ( (player==Player::player1) ? Player::player2 : Player::player1 );
    Outcome current_outcome = this->outcome();

    if( current_outcome == Outcome::draw )return { 0, {0,0} };
    if( (char)current_outcome == (char)opposite_player ) return { LEAF_VALUE - depth, {0,0} };
    else if( current_outcome != Outcome::none ) return { -LEAF_VALUE + depth , {0,0} };

    for(int row=0; row<BOARD_SIZE; ++row)
    {
        for(int column=0; column<BOARD_SIZE; ++column)
        {
            if( this->legal_move( {row,column} ) )
            {
                this->board[row][column] = player;

                temp = maxsearch( opposite_player, depth+1, alpha, beta );
                if( temp.first < minimum )
                {
                    return_value.first = temp.first;
                    return_value.second = { row , column };
                    minimum = temp.first;
                }

                if( temp.first < beta )
                    beta = temp.first;

                this->board[row][column] = Player::none;

                if( beta < alpha )
                    return return_value;
            }
        }
    }

    return return_value;
}

std::pair<int, Move_input> Minimax::maxsearch(Player player, int depth, int alpha, int beta)
{
    int maximum = std::numeric_limits<int>::min();
    std::pair<int, Move_input> return_value, temp;
    Player opposite_player = ( (player==Player::player1) ? Player::player2 : Player::player1 );
    Outcome current_outcome = this->outcome();

    if( current_outcome == Outcome::draw )return { 0, {0,0} };
    if( (char)current_outcome == (char)player ) return { LEAF_VALUE - depth , {0,0} };
    else if( current_outcome != Outcome::none ) return { -LEAF_VALUE + depth , {0,0} };

    for(int row=0; row<BOARD_SIZE; ++row)
    {
        for(int column=0; column<BOARD_SIZE; ++column)
        {
            if( this->legal_move( {row,column} ) )
            {
                this->board[row][column] = player;

                temp = minsearch( opposite_player, depth+1, alpha, beta );
                if( temp.first > maximum )
                {
                    return_value.first = temp.first;
                    return_value.second = { row, column };
                    maximum = temp.first;
                }

                if( temp.first > alpha )
                    alpha = temp.first;

                this->board[row][column] = Player::none;

                if( beta < alpha )
                    return return_value;
            }
        }
    }

    return return_value;
}

Move_input Minimax::computer_move(std::array<Player, BOARD_SIZE*BOARD_SIZE> input_board, Player player)
{
    int index=0;
    for(int row=0; row<BOARD_SIZE; ++row)
    {
        for(int column=0; column<BOARD_SIZE; ++column)
        {
            this->board[row][column]=input_board[index++];
        }
    }
    return maxsearch(player, 0, std::numeric_limits<int>::min(), std::numeric_limits<int>::max() ).second;
}

