/*         bool isMoveLegal(Board &board, int startX, int startY, int endX, int endY);
        std::vector<std::tuple<int, int, int, int>> getLegalMoves(Board &board);
        bool isCheck(Board &board, int color);
        bool isMate(Board &board, int color);
        bool isStale(Board &board);

 */
#include "Judge.h"

class Board;

bool Judge::isMoveLegal(Board &board, int startX, int startY, int endX, int endY, char pieceType){
    if(pieceType == 'p'){
        if(!wPawnRule(board, startX, startY, endX, endY)){return false;};

    }
    return true;
}

bool Judge::wPawnRule(Board &board, int startX, int startY, int endX, int endY){
    return true;
};
