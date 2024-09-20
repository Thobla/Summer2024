#include<math.h>
#include"Game.h"

Game::Game() : board(Board()), gui(Gui()), judge(Judge()), currPlayer(0){};

void Game::startGame(){};


void Game::swapPlayer(){
    currPlayer = (currPlayer + 1) % 2;
};


void Game::play(){
    gui.displayBoard(board);
    gui.makeMove(board, judge, currPlayer);
    swapPlayer();
    play();
};
    
int main(){
    Game game;
    game.play();

}
