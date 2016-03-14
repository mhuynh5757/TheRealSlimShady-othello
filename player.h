#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include "common.h"
#include "board.h"

using namespace std;

class Player
{
private:

    Side mySide;

    Side oppSide;

    Board * myBoard;

    int heuristicScore[8][8] = {
            { 20, -3, 11,  8,  8, 11, -3, 20},
            { -3, -7, -4,  1,  1, -4, -7, -3},
            { 11, -4,  2,  2,  2,  2, -4, 11},
            {  8,  1,  2, -3, -3,  2,  1,  8},
            {  8,  1,  2, -3, -3,  2,  1,  8},
            { 11, -4,  2,  2,  2,  2, -4, 11},
            { -3, -7, -4,  1,  1, -4, -7, -3},
            { 20, -3, 11,  8,  8, 11, -3, 20},
    };

    int score_board(Board b, Side s);

    int negascout(Board board, Side side, int alpha, int beta, int depth);

public:

    Player(Side side);

    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
