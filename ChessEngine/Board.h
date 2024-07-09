#ifndef BOARD_H
#define BOARD_H
#include <vector>


class Board{
    public:
        Board();
        void initializeBoard();
        void makeMove(int startX, int startY, int endX, int endY);
        unsigned long long getBitboard(char pieceType);
        void setBitboard(char pieceType, long long bitBoard);
        std::vector<char> getChars();

    private:
        unsigned long long wPawns, wKnights, wBishops, wRooks, wQueens, wKing;
        unsigned long long bPawns, bKnights, bBishops, bRooks, bQueens, bKing;
        unsigned long long occupiedSquares, freeSquares;
        std::vector<char> chars;
        void updateSquares();

};

#endif // BOARD_H
