#pragma once  
#include <fstream>  
#include<nlohmann/json.hpp>
#include "string.h"
using json = nlohmann::json;
using namespace std;

class FileHandler  
{  
public:
    nlohmann::json dataArray;

    void jsonWrite(stack<Score> scores) {
        json dataScore;
        int i = 0; 
        while (!scores.empty() && i < 10)
        {
            dataScore["Value"] = scores.top().value;
            dataScore["userName"] = scores.top().userName;
            dataArray.push_back(dataScore);
            scores.pop();
            i++;
        }
        std::ofstream o("scores.json");

        o << setw(4) << dataArray << endl;
        o.close();
    }

    stack<Score> jsonRead()
    {
        std::ifstream input("scores.json");
        stack<Score> scores;
        input >> dataArray;

        for (json j : dataArray)
        {
            Score temp = Score(j["Value"], j["userName"]);
            scores.push(temp);
        }
        input.close();
        return scores;
    }

};
