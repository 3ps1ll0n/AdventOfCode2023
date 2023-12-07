#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "function.hpp"
#include "Converter.hpp"

int main(){
    std::ifstream input("input.txt");
    std::string seedLine;
    std::getline(input, seedLine);
    seedLine.erase(0, seedLine.find(" ")+ 1);

    Converter* converter = new Converter();
    converter->init("input.txt");

    std::vector<long long> seeds = strToIntForVector(split(seedLine, " "));
    std::vector<std::string> keys = converter->getKeys();

    for(auto key : keys){
        std::cout << key << std::endl;
        for(int i = 0; i < seeds.size(); i++){
            seeds.at(i) = converter->convert(key, seeds.at(i));
        }
        //std::cout << seeds << std::endl;
    }

    displaySmaller(seeds);
}