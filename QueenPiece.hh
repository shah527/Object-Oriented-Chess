#ifndef __QUEENPIECE_H__
#define __QUEENPIECE_H__

#include "ChessPiece.hh"

namespace Student
{
    class QueenPiece : public ChessPiece
    {
    public:
        QueenPiece(ChessBoard &board, Color color, int row, int col);
        bool canMoveToLocation(int toRow, int toColumn) override;
        const char *toString() override;
    };
}

#endif // __QUEENPIECE_H__
