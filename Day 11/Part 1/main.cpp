#include <iostream>

#include "functions.hpp"

int main(){
    dMatrix<char> univers = init("input.txt");
    std::cout << univers << std::endl;
    univers = expandsUnivers(univers);
    std::cout << univers << std::endl;
    std::cout << sumOfDistances(univers) << std::endl;
}