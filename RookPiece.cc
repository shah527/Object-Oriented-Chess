#include "RookPiece.hh"
#include "ChessBoard.hh"

using namespace Student;

RookPiece::RookPiece(ChessBoard &board, Color color, int row, int col) : ChessPiece(board, color, row, col)
{
    type = Rook;
}

bool RookPiece::canMoveToLocation(int toRow, int toColumn)
{
    if (toRow < 0 || toRow >= board.getNumRows() || toColumn < 0 || toColumn >= board.getNumCols())
        return false;
    if (toRow == row && toColumn == col)
        return false;

    if (toRow == row || toColumn == col)
    {
        int a;
        int b;

        if (toRow > row)
            a = 1;
        else
            a = (toRow < row) ? -1 : 0;
        if (toColumn > col)
            b = 1;
        else
            b = (toColumn < col) ? -1 : 0;

        for (int r = row + a, c = col + b; r != toRow || c != toColumn; r += a, c += b)
        {
            if (board.getPiece(r, c) != nullptr)
                return false;
        }

        return true;
    }

    return false;
}

const char *RookPiece::toString()
{
    return (color == Black) ? "♜" : "♖";
}
