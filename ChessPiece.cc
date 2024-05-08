#include "ChessPiece.hh"
using namespace Student;

ChessPiece::ChessPiece(ChessBoard &board, Color color, int row, int column) : board(board), color(color), row(row), col(column) {}
Color ChessPiece::getColor() { return color; }
Type ChessPiece::getType() { return type; }
int ChessPiece::getRow() { return row; }
int ChessPiece::getColumn() { return col; }

void ChessPiece::setPosition(int row, int column)
{
    this->row = row;
    this->col = column;
}
