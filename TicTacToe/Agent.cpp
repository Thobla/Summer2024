#include<iostream>
#include<string>
#include<algorithm>
#include<math.h>
#include<vector>
#include<array>
#include<sstream>
#include "Game.cpp"

class Agent{
    public:
        Agent(Tic_Tac_Game *ex_game) : game(ex_game), map_act_pos(9), map_pos_act(3, std::vector<int>(3)){

        };

        struct Environment{
            int x_table;
            int o_table;
            int blank_table;
            int reward;
        };

        Environment step(int action){
            game->step(1, map_act_pos[action]);

            return;
        };

    private:
        Tic_Tac_Game *game;
        std::vector<std::array<int, 2>> map_act_pos;
        std::vector<std::vector<int>> map_pos_act;

        void init_maps(){
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    map_pos_act[i][j] = i*3 + j;
                    map_act_pos[i*3 + j] = {i, j};
                }
            }
        }
};


