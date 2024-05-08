#include "BishopPiece.hh"
#include "ChessBoard.hh"

using namespace Student;

BishopPiece::BishopPiece(ChessBoard &board, Color color, int row, int col) : ChessPiece(board, color, row, col)
{
  type = Bishop;
}

bool BishopPiece::canMoveToLocation(int toRow, int toColumn)
{
  int rowDiff = toRow - getRow();
  int columnDiff = toColumn - getColumn();

  if (toRow < 0 || toRow >= board.getNumRows() || toColumn < 0 || toColumn >= board.getNumCols())
    return false;

  ChessPiece *piece = board.getPiece(toRow, toColumn);
  if (piece == nullptr || piece->getColor() != getColor())
  {
    if (rowDiff != 0 && columnDiff != 0 && abs(rowDiff) == abs(columnDiff))
    {
      int a;
      int b;
      if (rowDiff > 0)
        a = 1;
      else
        a = -1;
      if (columnDiff > 0)
        b = 1;
      else
        b = -1;

      int r = getRow() + a;
      int c = getColumn() + b;
      while (r != toRow || c != toColumn)
      {
        if (board.getPiece(r, c) != nullptr)
        {
          return false;
        }
        r += a;
        c += b;
      }

      return true;
    }
  }

  return false;
}

const char *BishopPiece::toString()
{
  return (color == Black) ? "♝" : "♗";
}
