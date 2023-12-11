#include <iostream>
#include <vector>
#include <string>

#include "functions.hpp"



int main(){
    Race* race;
    init(&race);

    long long sum = 0;
    long long canWin = 0;

    long long time = race->time;
    long long distanceToBeat = race->distance;
    long long traveledDistance = 0;
    long long speed = 0;
    long long winningPossibility = 0;

    for(long i = 0; i <= time; i ++){
        speed = i;
        traveledDistance = speed * (time - i);
        if(traveledDistance > distanceToBeat) {
            std::cout << traveledDistance << " : " << distanceToBeat << std::endl;
            canWin = i;
            break;
        }
    }
    std::cout << canWin << std::endl;
    sum = race->time - (2*canWin) + 1;

    std::cout << sum << std::endl;
}