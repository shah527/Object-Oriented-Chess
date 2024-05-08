#include "PawnPiece.hh"
#include "ChessBoard.hh"

using namespace Student;

PawnPiece::PawnPiece(ChessBoard &board, Color color, int row, int col) : ChessPiece(board, color, row, col)
{
    type = Pawn;
}

bool PawnPiece::canMoveToLocation(int toRow, int toColumn)
{
    int direction;
    if (color == Black)
        direction = 1;
    else
        direction = -1; 

    int rowDiff = toRow - getRow();
    int columnDiff = toColumn - getColumn();

    if (toRow < 0 || toRow >= board.getNumRows() || toColumn < 0 || toColumn >= board.getNumCols())
        return false;

    if (rowDiff == direction && abs(columnDiff) == 1)
    {
        ChessPiece *piece = board.getPiece(toRow, toColumn);
        if (piece != nullptr && piece->getColor() != color)
            return true;
    }

    if (columnDiff == 0)
    {
        if (rowDiff == direction)
        {
            if (board.getPiece(toRow, toColumn) == nullptr)
                return true;
            else
                return false;
        }
        else if (rowDiff == 2 * direction &&
                 ((color == Black && getRow() == 1) ||
                  (color == White && getRow() == board.getNumRows() - 2)))
        {
            if (board.getPiece(toRow - direction, toColumn) == nullptr &&
                board.getPiece(toRow, toColumn) == nullptr)
                return true;
            else
                return false;
        }
    }

    return false;
}

const char *PawnPiece::toString()
{
    return (color == Black) ? "♟" : "♙";
}
