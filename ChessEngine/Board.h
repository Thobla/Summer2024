#ifndef BOARD_H
#define BOARD_H
#include <vector>


class Board{
    public:
        void initializeBoard();
        void makeMove(int startX, int startY, int endX, int endY);
        long long getBitboard(char pieceType);
        void setBitboard(char pieceType, long long bitBoard);
        std::vector<char> getChars();

    private:
        long long wPawns, wKnights, wBishops, wRooks, wQueens, wKing;
        long long bPawns, bKnights, bBishops, bRooks, bQueens, bKing;
        long long occupiedSquare, freeSquare;
        std::vector<char> chars;

};

#endif // BOARD_H
