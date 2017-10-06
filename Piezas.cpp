#include "Piezas.h"
#include <vector>

/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
    turn = X;
    for(int i = 0; i < BOARD_ROWS; i++) {
        std::vector<Piece> row;
        board.push_back(row);
        for(int j = 0; j < BOARD_COLS; j++) {
            board.at(i).push_back(Blank);
        }
    }
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
    for(int i = 0; i < BOARD_ROWS; i++) {
        for(int j = 0; j < BOARD_COLS; j++) {
            board[i][j] = Blank;
        }
    }
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column)
{
    Piece local_turn = turn;
    turn = turn == X ? O : X;
    if (column < BOARD_COLS && column >= 0) {
        for(int i = 0; i < BOARD_ROWS; i++) {
            if(board[i][column] == Blank) {
                board[i][column] = local_turn;
                return local_turn;
            }
        }
        return Blank;
    }
    return Invalid;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
    return(row < BOARD_ROWS && row >= 0 && column < BOARD_COLS && column >= 0 ? board[row][column] : Invalid);
}


/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
    for(int i = 0; i < BOARD_ROWS; i++) {
        for(int j = 0; j < BOARD_COLS; j++) {
            if(board[i][j] == Blank) {
                return Invalid;
            }
        }
    }
    
    int X_Horizontal = 0;
    int O_Horizontal = 0;
    
   
    for(int i = 0; i < BOARD_ROWS; i++) {
        int Local_X_Horizontal = 0;
        int Local_O_Horizontal = 0;
        for(int j = 0; j < BOARD_COLS; j++) {
            if(pieceAt(i,j) == pieceAt(i,j+1)) {
                pieceAt(i,j) == X ? Local_X_Horizontal += 1 : Local_O_Horizontal += 1; 
            }
        }
        X_Horizontal = Local_X_Horizontal >= X_Horizontal && Local_X_Horizontal != 0 ? Local_X_Horizontal + 1 : X_Horizontal;
        O_Horizontal = Local_O_Horizontal >= O_Horizontal && Local_O_Horizontal != 0 ? Local_O_Horizontal + 1 : O_Horizontal;
    }
    
    int X_Vertical = 0;
    int O_Vertical = 0;
   
    for(int j = 0; j < BOARD_COLS; j++) {
        int Local_X_Vertical = 0;
        int Local_O_Vertical = 0;
        for(int i = 0; i < BOARD_ROWS; i++) {
            if(pieceAt(i,j) == pieceAt(i+1,j)) {
               pieceAt(i,j) == X ? Local_X_Vertical += 1 : Local_O_Vertical += 1; 
            }
        }
        X_Vertical = Local_X_Vertical >= X_Vertical && Local_X_Vertical != 0 ? Local_X_Vertical + 1 : X_Vertical;
        O_Vertical = Local_O_Vertical >= O_Vertical && Local_O_Vertical != 0 ? Local_O_Vertical + 1 : O_Vertical;
    }
    
    int X_Max = X_Horizontal > X_Vertical ? X_Horizontal : X_Vertical;
    int O_Max = O_Horizontal > O_Vertical ? O_Horizontal : O_Vertical;
    
    return (X_Max == O_Max ? Blank : X_Max > O_Max ? X : O);
}

/*
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 */