#include<string>
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


