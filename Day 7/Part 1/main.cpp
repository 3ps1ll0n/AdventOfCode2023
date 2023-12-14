#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Hand.hpp"
#include "functions.hpp"

int main(){
    std::vector<Hand*> allHands = init("input.txt");
    
    allHands = sortHands(allHands);
    std::cout << allHands;
    std::cout << totalWinning(allHands);
}