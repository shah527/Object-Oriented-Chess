#ifndef __KNIGHTPIECE_H__
#define __KNIGHTPIECE_H__

#include "ChessPiece.hh"

namespace Student
{
    class KnightPiece : public ChessPiece
    {
    public:
        KnightPiece(ChessBoard &board, Color color, int row, int col);
        bool canMoveToLocation(int toRow, int toColumn) override;
        const char *toString() override;
    };
}

#endif // __KNIGHTPIECE_H__
