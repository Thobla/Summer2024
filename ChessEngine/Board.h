#ifndef BOARD_H
#define BOARD_H


class Board{
    public:
        void initializeBoard();
        void makeMove(int startX, int startY, int endX, int endY);
        long long getBitboard(char pieceType);
        void setBitboard(char pieceType, long long bitBoard);

    private:
        long long wPawns, wKnights, wBishops, wRooks, wQueens, wKing;
        long long bPawns, bKnights, bBishops, bRooks, bQueens, bKing;
        long long occupiedSquare, freeSquare;

};

#endif // BOARD_H
