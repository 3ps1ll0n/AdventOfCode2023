#pragma once

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>

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