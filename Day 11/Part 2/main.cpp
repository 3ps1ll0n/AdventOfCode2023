#include <iostream>

#include "functions.hpp"

int main(){
    dMatrix<char> univers = init("input.txt");
    findExpandationPoints(univers);
    std::cout << sumOfDistances(univers) << std::endl;
}