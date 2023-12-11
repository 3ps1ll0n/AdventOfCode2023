#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>

#include "function.hpp"
#include "Converter.hpp"

long long calculateSmalest(std::vector<long long> seedSet, Converter* converter){
    std::vector<long long> allSeeds = {};
    std::vector<Range*> ranges = {};
    std::vector<std::string> keys = converter->getKeys();
    std::vector<Range*> temp = {};
    
    for(int j = 0; j < seedSet.size(); j+=2){
        ranges.push_back(new Range(seedSet.at(j), seedSet.at(j) + seedSet.at(j + 1), seedSet.at(j+1)));
    }
    for(auto key : keys){
        temp = {};
        std::cout << key << std::endl;
        std::cout << ranges.size() << std::endl;
        append(&temp, converter->generateRangefromeRanges(ranges, key));
        ranges = temp;
        //std::cout << converter->getBeginValueOfRanges(ranges) << std::endl;
    }
    ranges = temp;
    return displaySmaller(converter->getBeginValueOfRanges(ranges));
}

int main(){
    std::ifstream input("input.txt");
    std::string seedLine;
    std::getline(input, seedLine);
    seedLine.erase(0, seedLine.find(" ")+ 1);

    Converter converter = Converter();
    converter.init("input.txt");

    std::vector<long long> seeds = strToIntForVector(split(seedLine, " "));
    std::vector<long long> lowestSeeds = {};

    std::cout << calculateSmalest(seeds, &converter) << std::endl;
}