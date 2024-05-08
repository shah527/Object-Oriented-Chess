#include "KingPiece.hh"
#include "ChessBoard.hh"

using namespace Student;

KingPiece::KingPiece(ChessBoard &board, Color color, int row, int col) : ChessPiece(board, color, row, col)
{
  type = King;
}

bool KingPiece::canMoveToLocation(int toRow, int toColumn)
{
  if (toRow < 0 || toRow >= board.getNumRows() || toColumn < 0 || toColumn >= board.getNumCols())
  {
    return false;
  }
  if (toRow == row && toColumn == col)
  {
    return false;
  }

  return (abs(toRow - row) <= 1 && abs(toColumn - col) <= 1);
}

const char *KingPiece::toString()
{
  return (color == Black) ? "♚" : "♔";
}
