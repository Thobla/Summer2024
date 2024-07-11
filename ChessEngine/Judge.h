#ifndef JUDGE_H
#define JUDGE_H

#include <vector>

class Board;

class Judge{
    public:
        bool isMoveLegal(Board &board, int startX, int startY, int endX, int endY, char pieceType);
        std::vector<std::tuple<int, int, int, int>> getLegalMoves(Board &board);
        bool isCheck(Board &board, int color);
        bool isMate(Board &board, int color);
        bool isStale(Board &board);

        bool wPawnRule(Board &board, int startX, int startY, int endX, int endY);
        bool wKnightRule(Board &board, int startX, int startY, int endX, int endY);
        bool wBishopRule(Board &board, int startX, int startY, int endX, int endY);
        bool wRookRule(Board &board, int startX, int startY, int endX, int endY);
        bool wQueenRule(Board &board, int startX, int startY, int endX, int endY);
        bool wKingRule(Board &board, int startX, int startY, int endX, int endY);

        bool bPawnRule(Board &board, int startX, int startY, int endX, int endY);
        bool bKnightRule(Board &board, int startX, int startY, int endX, int endY);
        bool bBishopRule(Board &board, int startX, int startY, int endX, int endY);
        bool bRookRule(Board &board, int startX, int startY, int endX, int endY);
        bool bQueenRule(Board &board, int startX, int startY, int endX, int endY);
        bool bKingRule(Board &board, int startX, int startY, int endX, int endY);

        bool pathCleared(Board &board, int startX, int startY, int endX, int endY);


};


#endif // JUDGE_H
