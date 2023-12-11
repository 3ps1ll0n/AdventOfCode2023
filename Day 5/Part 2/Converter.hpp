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
    std::vector<Range*> generateRangefromeRanges(std::vector<Range*> allRanges, std::string map);
    std::vector<long long> getBeginValueOfRanges(std::vector<Range*> allRanges);
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

std::vector<Range*> Converter::generateRangefromeRanges(std::vector<Range*> allRanges, std::string map){
    if(allRange.find(map) == allRange.end()){
        std::cout << "Can't find the map" << std::endl;
        return {};
    } 

    std::vector<Range*> rangesToCompare = allRange.find(map)->second;
    std::vector<Range*> newRanges = {};

    for(Range* formerRange : allRanges){
        bool asAlreadyBeenReturn = false;
        for(int i = 0; i < rangesToCompare.size(); i++){
            Range* comparRange = rangesToCompare.at(i);
            std::vector<Range*> t = comparRange->generateRangeFromRange(formerRange);
            if ((t.size() == 1 && t.at(0)->getBegin() != formerRange->getBegin()) || t.size() >= 2){
                append(&newRanges, t);
                break;
            } else if( i == rangesToCompare.size() - 1) newRanges.push_back(formerRange);
            
        }
    }
    return newRanges;
}

std::vector<long long> Converter::getBeginValueOfRanges(std::vector<Range*> allRanges){
    std::vector<long long> beginValues = {};

    std::cout << allRanges.size() << std::endl;

    for(auto range : allRanges){
        beginValues.push_back(range->getBegin());
    }

    return beginValues;
}
