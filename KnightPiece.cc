#include "KnightPiece.hh"
#include "ChessBoard.hh"

using namespace Student;

KnightPiece::KnightPiece(ChessBoard &board, Color color, int row, int col) : ChessPiece(board, color, row, col)
{
    type = Knight;
}

bool KnightPiece::canMoveToLocation(int toRow, int toColumn)
{
    if (toRow < 0 || toRow >= board.getNumRows() || toColumn < 0 || toColumn >= board.getNumCols())
        return false;
    if (toRow == row && toColumn == col)
        return false;

    int rowDiff = abs(toRow - row);
    int colDiff = abs(toColumn - col);
    return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
}

const char *KnightPiece::toString()
{
    return (color == Black) ? "♞" : "♘";
}
