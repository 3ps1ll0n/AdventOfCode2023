#include "functions.hpp"

#include <vector>
#include <iostream>

int main(){
    std::vector<std::vector <int>> nbreSets = init("input.txt");
    std::cout << calculatePredictions(nbreSets) << std::endl;
}