#pragma once

#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>

#include "Range.hpp"
#include "function.hpp"

class Converter
{
private:
    std::map<std::string, std::vector<Range*>> allRange;
    std::vector<std::string> keys;
public:
    Converter();
    ~Converter();
    void init(std::string fileLocation);
    long long convert(std::string map, long long valueToConvert);
    std::vector<std::string> getKeys();
    int getLowerRange(std::string map);
};

Converter::Converter()
:keys({}){}

Converter::~Converter(){}

void Converter::init(std::string fileLocation){
    std::ifstream input(fileLocation);
    std::string line = "";
    std::string lastMap = "";
    std::getline(input, line);
    std::getline(input, line);
    
    while (std::getline(input, line))
    {
        std::vector<std::string> arguments = split(line, " ");
        if(!arguments.at(0).empty()) {
            if(arguments.at(1) == "map:" && allRange.find(arguments.at(0)) == allRange.end()){
                allRange.insert(std::pair<std::string, std::vector<Range*>>(arguments.at(0), {}));
                keys.push_back(arguments.at(0));
                lastMap = arguments.at(0);
            }
            else {
                std::vector<long long> values = strToIntForVector(arguments);
                allRange.find(lastMap)->second.push_back(new Range(values.at(1), values.at(1) + values.at(2) - 1, values.at(0) - values.at(1)));
            }
        }
    }
    
}

long long Converter::convert(std::string map, long long valueToConvert){
    if(allRange.find(map) == allRange.end()){
        std::cout << "Can't find the map" << std::endl;
        return -1;
    } 

    std::vector<Range*> ranges = allRange.find(map)->second;

    for(Range* range : ranges){
        if(range->isInRange(valueToConvert)){
            return range->convertNbre(valueToConvert);
        }
    }
    return valueToConvert;
}

std::vector<std::string> Converter::getKeys(){
    return keys;
}
