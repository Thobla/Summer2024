#include<iostream>
#include<string>
#include<algorithm>
#include<math.h>
#include<vector>
#include<sstream>

/*
 * Helper functions
 */

std::vector<std::string> split(std::string &s, char delimiter){
    std::vector<std::string> final_s;
    std::string temp_s;
    std::istringstream stream(s);

    while (std::getline(stream, temp_s, delimiter)){
        final_s.push_back(temp_s);
    };

    return final_s;
};

class Tic_Tac_Game{
    public:
        Tic_Tac_Game()
            : tic_tac_terminated(0){
        };

        void run(){
            while (!state.terminated){
                step();

            }
        };

    private:
        struct Game_state{
            int terminated;
            int curr_player;
            Game_state() : terminated(0), curr_player(0) {};
        };

        struct Player{
            std::string name;
            char symbol;
        };
        struct Board{
            int tile_count;
            int x_table;
            int o_table;
            int blank_table;
            Board() : tile_count(9), x_table(0), o_table(0), blank_table((1<<9) - 1) {};
        };

        int tic_tac_terminated;
        Board tic_tac_board;
        Game_state state; 
        Player p1 = {"Player 1", 'x'};
        Player p2 = {"Player 2", 'o'};

        void step(){
            int x, y;
            std::vector<std::string> command;
            if (state.curr_player == 0){
                std::cout << p1.name + " It's your move \n";
            }
            else if (state.curr_player == 1){
                std::cout << p2.name + " It's your move \n";
            };
            std::cout <<"type in your move as 'x y'.\n";
            std::cin >> command; //Need to refactor at some time to check input correctness
            command = split(command, " ");
            x = stoi(command[0]);
            y = stoi(command[1]);
            if ((x < 3 && x > 1) || (y < 3 && y > 1)){

            }

            perform_placement(x, y, state.curr_player);
        };

};




int main(){
    return 0;
    }    

