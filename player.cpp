#include "player.h"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side)
{
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */

    myBoard = new Board();

    mySide = side;

    if (side == WHITE)
    {
        oppSide = BLACK;
    }
    else
    {
        oppSide = WHITE;
    }

}

int Player::score_board(Board b, Side s)
{
    Side oppSide;
    if (s == WHITE)
    {
        oppSide = BLACK;
    }
    else
    {
        oppSide = WHITE;
    }
    int score = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(b.get(s, j, i))
            {
                score += heuristicScore[j][i];
            }
            else if (b.get(oppSide, j, i))
            {
                score -= heuristicScore[j][i];
            }
        }
    }
    return score;
}

vector<Move*> findPossibleMoves(Board b, Side s)
{
    vector<Move*> moves;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Move * m = new Move(j, i);
            if (b.checkMove(m, s))
            {
                moves.push_back(m);
            }
        }
    }
    return moves;
}

/*
 * Destructor for the player.
 */
Player::~Player()
{
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft)
{
    if (opponentsMove != NULL)
    {
        myBoard->doMove(opponentsMove, oppSide);
    }

    if (!myBoard->hasMoves(mySide))
    {
        return NULL;
    }

    vector<Move*> possible_moves = findPossibleMoves(*myBoard, mySide);

    int max_score = -1000000;
    Move *best_move = possible_moves.at(0);
    for (unsigned int i = 0; i < possible_moves.size(); i++)
    {
        Board * new_board = myBoard->copy();
        new_board->set(mySide, possible_moves.at(i)->getX(), possible_moves.at(i)->getY());
        int score = -negascout(*new_board, oppSide, -1000, 1000, 5);
        if (max_score < score)
        {
            max_score = score;
            best_move = possible_moves.at(i);
        }
    }

    myBoard->doMove(best_move, mySide);
    return best_move;
}

int Player::negascout(Board board, Side side, int alpha, int beta, int depth)
{
    Side oppSide;
    if (side == WHITE)
    {
        oppSide = BLACK;
    }
    else
    {
        oppSide = WHITE;
    }
    if (!board.hasMoves(side) || depth <= 0)
    {
        return score_board(board, side);
    }
    vector<Move*> possible_moves = findPossibleMoves(board, side);
    for (unsigned int i = 0; i < possible_moves.size(); i++)
    {
        Board * new_board = board.copy();
        new_board->set(side, possible_moves.at(i)->getX(), possible_moves.at(i)->getY());
        int score;
        if (i > 0)
        {
            score = -negascout(*new_board, oppSide, -alpha - 1, -alpha, depth - 1);
            if (alpha < score && score < beta)
            {
                score = -negascout(*new_board, oppSide, -beta, -score, depth - 1);
            }
        }
        else
        {
            score = -negascout(*new_board, oppSide, -beta, -alpha, depth - 1);
        }
        alpha = max(alpha, score);
        if (alpha >= beta)
        {
            return alpha;
        }
    }
    return alpha;
}