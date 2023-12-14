#pragma once

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <numeric>

#include "functions.hpp"

class Map
{
private:
    std::vector<char> instructions;
    std::map<std::string, std::pair<std::string, std::string>> map;
public:
    Map();
    ~Map();
    void init(std::string inputFile);
    int calcultePathSteps();
    long long calculateStepsGhost();
};

Map::Map(/* args */)
{
}

Map::~Map()
{
}

void Map::init(std::string inputFile) {
    std::ifstream input(inputFile);
    std::string line = "";
    std::getline(input, line);

    for(char c : line)
        instructions.push_back(c);

    std::getline(input, line);
    
    while (std::getline(input, line))
    {
        std::vector<std::string> params = split(line, " = ");
        std::string path = params.at(1);

        path.erase(0, 1);
        path.erase(path.end() - 1, path.end());
        std::vector<std::string> paths = split(path, ", ");

        map.insert(std::pair(params.at(0), std::pair(paths.at(0), paths.at(1))));
    }
    
}

int Map::calcultePathSteps(){
    int steps = 0;
    int pointerToInstructions = 0;
    std::string toCherche = "AAA";

    do{
        steps++;
        char leftOrRight = instructions.at(pointerToInstructions);
        if(++pointerToInstructions >= instructions.size()) pointerToInstructions = 0;
        std::pair<std::string, std::string> paths = map.find(toCherche)->second;
        if(leftOrRight == 'R') toCherche = paths.second;
        else toCherche = paths.first;
    }while(toCherche != "ZZZ");

    return steps;
}

long long Map::calculateStepsGhost(){
    long long totalSteps = 1;
    int steps = 0;
    int pointerToInstructions = 0;
    std::vector<std::string> toCherche = {};
    bool isAllArrived = false;
    
    for(std::map<std::string, std::pair<std::string, std::string>>::iterator it = map.begin(); it != map.end(); ++it){
        if(it->first.at(it->first.size() - 1) == 'A') {
            toCherche.push_back(it->first);
        }
    }

    std::vector<int> posWhenArrived(toCherche.size());
    std::cout << posWhenArrived.size() << std::endl;

    do{
        steps++;
        char leftOrRight = instructions.at(pointerToInstructions);
        if(++pointerToInstructions >= instructions.size()) pointerToInstructions = 0;

        std::vector<std::string> temps = {};
    
        for(int i = 0; i < toCherche.size(); i++){
            std::string str = toCherche.at(i);
            std::pair<std::string, std::string> paths = map.find(str)->second;
            if(leftOrRight == 'R') temps.push_back(paths.second);
            else temps.push_back(paths.first);
            auto path = temps.at(temps.size() - 1);
            if(path.at(path.size() - 1) == 'Z') {
                if(posWhenArrived.at(i) == 0) posWhenArrived[i] = steps;
            }
            
        }
        toCherche = temps;

        int isFull = 0;
        for(int i : posWhenArrived){
            if(i != 0) isFull++;
        }

        if(isFull == posWhenArrived.size()) {
            totalSteps = std::lcm(std::lcm(std::lcm(posWhenArrived.at(0), posWhenArrived.at(1)), posWhenArrived.at(2)), std::lcm(std::lcm(posWhenArrived.at(5), posWhenArrived.at(3)), posWhenArrived.at(4)));
        }
    }while(totalSteps <= 1);

    return totalSteps;
}