#include "ChessBoard.hh"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"
#include "KnightPiece.hh"
#include "QueenPiece.hh"

using Student::ChessBoard;

std::ostringstream ChessBoard::displayBoard()
{
  std::ostringstream outputString;
  outputString << "  ";
  for (int i = 0; i < numCols; i++)
  {
    outputString << i;
  }
  outputString << std::endl
               << "  ";
  for (int i = 0; i < numCols; i++)
  {
    outputString << "-";
  }
  outputString << std::endl;

  for (int row = 0; row < numRows; row++)
  {
    outputString << row << "|";
    for (int column = 0; column < numCols; column++)
    {
      ChessPiece *piece = board.at(row).at(column);
      outputString << (piece == nullptr ? " " : piece->toString());
    }
    outputString << "|" << std::endl;
  }

  outputString << "  ";
  for (int i = 0; i < numCols; i++)
  {
    outputString << "-";
  }
  outputString << std::endl
               << std::endl;

  return outputString;
}

ChessBoard::ChessBoard(int numRow, int numCol) : numRows(numRow), numCols(numCol)
{
  board = std::vector<std::vector<ChessPiece *>>(numRow, std::vector<ChessPiece *>(numCol, nullptr));
  whiteKingLocation = nullptr;
  blackKingLocation = nullptr;
}

void ChessBoard::createChessPiece(Color col, Type ty, int startRow, int startColumn)
{
  if (startRow < 0 || startRow >= numRows || startColumn < 0 || startColumn >= numCols)
  {
    return;
  }

  ChessPiece *piece = nullptr;
  if (ty == Rook)
  {
    piece = new RookPiece(*this, col, startRow, startColumn);
    if (piece == nullptr)
    {
      return;
    }
  }
  else if (ty == Bishop)
  {
    piece = new BishopPiece(*this, col, startRow, startColumn);
    if (piece == nullptr)
    {
      return;
    }
  }
  else if (ty == Pawn)
  {
    piece = new PawnPiece(*this, col, startRow, startColumn);
    if (piece == nullptr)
    {
      return;
    }
  }
  else if (ty == King)
  {
    piece = new KingPiece(*this, col, startRow, startColumn);
    if (piece == nullptr)
    {
      return;
    }
    if (col == Black)
    {
      blackKingLocation = piece;
    }
    else
    {
      whiteKingLocation = piece;
    }
  }
  else if (ty == Knight)
  {
    piece = new KnightPiece(*this, col, startRow, startColumn);
    if (piece == nullptr)
    {
      return;
    }
  }
  else if (ty == Queen)
  {
    piece = new QueenPiece(*this, col, startRow, startColumn);
    if (piece == nullptr)
    {
      return;
    }
  }
  else
  {
    return;
  }

  if (board.at(startRow).at(startColumn) != nullptr)
    delete board.at(startRow).at(startColumn);

  board.at(startRow).at(startColumn) = piece;
}

bool ChessBoard::movePiece(int fromRow, int fromColumn, int toRow, int toColumn)
{
  if (fromRow < 0 || fromRow >= numRows || fromColumn < 0 || fromColumn >= numCols ||
      toRow < 0 || toRow >= numRows || toColumn < 0 || toColumn >= numCols)
  {
    return false;
  }
  ChessPiece *piece = getPiece(fromRow, fromColumn);
  if (!piece)
  {
    return false;
  }
  if (getPiece(fromRow, fromColumn)->getColor() != turn && getPiece(fromRow, fromColumn) != nullptr)
  {
    return false;
  }
  if (!isValidMove(fromRow, fromColumn, toRow, toColumn))
  {
    return false;
  }
  ChessPiece *destPiece = getPiece(toRow, toColumn);
  if (destPiece && destPiece->getColor() == piece->getColor())
  {
    return false;
  }
  if (destPiece)
  {
    delete destPiece;
    board.at(toRow).at(toColumn) = nullptr;
  }
  ChessPiece *board_check = board.at(toRow).at(toColumn);
  piece->setPosition(toRow, toColumn);
  board.at(toRow).at(toColumn) = piece;

  board.at(fromRow).at(fromColumn) = nullptr;
  turn = (turn == White) ? Black : White;
  if (piece->getType() == Pawn)
  {
    int promotionRow = (piece->getColor() == White) ? 0 : numRows - 1;
    if (toRow == promotionRow)
    {
      delete piece;
      board.at(toRow).at(toColumn) = new QueenPiece(*this, piece->getColor(), toRow, toColumn);
    }
  }

  if (board_check != nullptr && board_check->getType() == King)
  {
    if (board_check->getColor() == White)
    {
      whiteKingLocation = nullptr;
    }
    else
    {
      blackKingLocation = nullptr;
    }
    delete board_check;
  }

  return true;
}

bool ChessBoard::isValidMove(int fromRow, int fromColumn, int toRow, int toColumn)
{
  if (toRow < 0 || toRow >= numRows || toColumn < 0 || toColumn >= numCols)
    return false;

  ChessPiece *piece = getPiece(fromRow, fromColumn);
  if (piece == nullptr)
    return false;

  ChessPiece *destPiece = getPiece(toRow, toColumn);
  if (destPiece != nullptr && destPiece->getColor() == piece->getColor())
    return false;
  if (!isKingSafe(fromRow, fromColumn, toRow, toColumn))
    return false;

  return piece->canMoveToLocation(toRow, toColumn);
}

bool ChessBoard::isPieceUnderThreat(int row, int column)
{
  ChessPiece *targetPiece = getPiece(row, column);
  if (targetPiece == nullptr)
    return false;

  Color targetColor = targetPiece->getColor();
  for (int r = 0; r < numRows; ++r)
  {
    for (int c = 0; c < numCols; ++c)
    {
      ChessPiece *attackPiece = getPiece(r, c);
      if (attackPiece && attackPiece->getColor() != targetColor)
        if (attackPiece->canMoveToLocation(row, column))
          return true;
    }
  }

  return false;
}

bool ChessBoard::isKingSafe(int fromRow, int fromColumn, int toRow, int toColumn)
{
  ChessPiece *kingLocation = getPiece(fromRow, fromColumn)->getColor() == White ? whiteKingLocation : blackKingLocation;
  if (kingLocation == nullptr)
  {
    return true;
  }

  ChessPiece *stand_by = board.at(toRow).at(toColumn);
  getPiece(fromRow, fromColumn)->setPosition(toRow, toColumn);
  board.at(toRow).at(toColumn) = getPiece(fromRow, fromColumn);
  board.at(fromRow).at(fromColumn) = nullptr;
  bool isSafe = !isPieceUnderThreat(kingLocation->getRow(), kingLocation->getColumn());

  board.at(fromRow).at(fromColumn) = getPiece(toRow, toColumn);
  board.at(toRow).at(toColumn) = stand_by;
  getPiece(fromRow, fromColumn)->setPosition(fromRow, fromColumn);

  return isSafe;
}

float ChessBoard::scoreBoard() const
{
  // float score = 0.0;
  // for (int i = 0; i < 8; i++) {
  //     for (int j = 0; j < 8; j++) {
  //         if (auto piece = getPieceAt(i, j)) {
  //             score += piece->value();
  //             score += piece->legalMoves(*this).size() * 0.1;
  //         }
  //     }
  // }
  return 0.0;
}

float ChessBoard::getHighestNextScore()
{
  // float highestScore = -9999.0;
  // for (int i = 0; i < 8; i++) {
  //     for (int j = 0; j < 8; j++) {
  //         auto moves = getPieceAt(i, j)->legalMoves(*this);
  //         for (auto& move : moves) {
  //             movePiece(i, j, move.first, move.second);
  //             float score = scoreBoard();
  //             if (score > highestScore)
  //                 highestScore = score;
  //             //undoMove();
  //         }
  //     }
  // }
  return 0.0;
}

ChessBoard::~ChessBoard()
{
  for (auto &row : board)
  {
    for (auto &piece : row)
    {
      delete piece;
    }
  }
}
