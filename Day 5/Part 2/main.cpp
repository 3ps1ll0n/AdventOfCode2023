#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>

#include "function.hpp"
#include "Converter.hpp"

long long calculateSmalest(std::vector<long long> seedSet, int seedPos, Converter& converter){
    std::vector<long long> allSeeds = {};
    std::vector<std::string> keys = converter.getKeys();
    
    for(int j = 0; j < seedSet.at(seedPos+1); j++){
        allSeeds.push_back(seedSet.at(seedPos) + j);
    }
    for(auto key : keys){
        std::cout << key << std::endl;
        for(int i = 0; i < allSeeds.size(); i++){
            allSeeds.at(i) = converter.convert(key, allSeeds.at(i));
        }
    }
    return displaySmaller(allSeeds);
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
}