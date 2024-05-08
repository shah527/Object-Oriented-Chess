#ifndef _PAWNPIECE_H__
#define _PAWNPIECE_H__

#include "ChessPiece.hh"

namespace Student
{
    class PawnPiece : public ChessPiece
    {
    public:
        PawnPiece(ChessBoard &board, Color color, int row, int col);
        virtual bool canMoveToLocation(int toRow, int toColumn) override;
        const char *toString() override;
    };
}

#endif
