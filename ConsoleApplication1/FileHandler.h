#pragma once  
#include <fstream>  
#include<nlohmann/json.hpp>
#include "string.h"
#include "Score.h"
using json = nlohmann::json;
using namespace std;

class FileHandler
{
public:
    nlohmann::json dataArray;

    void jsonWrite(stack<Score> scores) {
        dataArray.clear();
        json dataScore;
        int i = 0;
        stack<Score> reversed;
        while (!scores.empty() && i < 10)
        {
            reversed.push(scores.top());
            scores.pop();
            i++;
        }


        while (!reversed.empty())
        {
            dataScore["Value"] = reversed.top().value;
            dataScore["userName"] = reversed.top().userName;
            dataArray.push_back(dataScore);
            reversed.pop();
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
        int i = 0;

        for (json j : dataArray)
        {
            Score temp = Score(j["Value"], j["userName"]);
            scores.push(temp);
            if (i > 10)
            {
                break;
            }
            i++;
        }
        input.close();
        return scores;
    }

};
