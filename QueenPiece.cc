#include "QueenPiece.hh"
#include "ChessBoard.hh"

using namespace Student;

QueenPiece::QueenPiece(ChessBoard &board, Color color, int row, int col) : ChessPiece(board, color, row, col)
{
    type = Queen;
}

bool QueenPiece::canMoveToLocation(int toRow, int toColumn)
{
    if (toRow < 0 || toRow >= board.getNumRows() || toColumn < 0 || toColumn >= board.getNumCols())
        return false;
    if (toRow == row && toColumn == col)
        return false;

    int rowDiff = toRow - row;
    int colDiff = toColumn - col;

    if (toRow == row || toColumn == col)
    {
        int stepRow = (toRow > row) ? 1 : ((toRow < row) ? -1 : 0);
        int stepCol = (toColumn > col) ? 1 : ((toColumn < col) ? -1 : 0);

        for (int r = row + stepRow, c = col + stepCol; r != toRow || c != toColumn; r += stepRow, c += stepCol)
        {
            if (board.getPiece(r, c) != nullptr)
                return false;
        }
        return true;
    }
    if (abs(rowDiff) == abs(colDiff))
    {
        int stepRow = (rowDiff > 0) ? 1 : -1;
        int stepCol = (colDiff > 0) ? 1 : -1;

        int r = row + stepRow;
        int c = col + stepCol;
        while (r != toRow || c != toColumn)
        {
            if (board.getPiece(r, c) != nullptr)
            {
                return false;
            }
            r += stepRow;
            c += stepCol;
        }
        return true;
    }
    return false;
}

const char *QueenPiece::toString()
{
    return (color == Black) ? "♛" : "♕";
}
