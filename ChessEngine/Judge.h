#ifndef JUDGE_H
#define JUDGE_H

#include <vector>

class Board;

class Judge{
    public:
        bool isMoveLegal(Board &board, int startX, int startY, int endX, int endY);
        std::vector<std::tuple<int, int, int, int>> getLegalMoves(Board &board);
        bool isCheck(Board &board, int color);
        bool isMate(Board &board, int color);
        bool isStale(Board &board);

};


#endif // JUDGE_H
