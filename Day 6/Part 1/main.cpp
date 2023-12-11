#include <iostream>
#include <vector>
#include <string>

#include "functions.hpp"



int main(){
    std::vector<Race*> races;
    init(&races);

    int sum = 1;

    for(Race* race : races){
        int time = race->time;
        int distanceToBeat = race->distance;
        int traveledDistance = 0;
        int speed = 0;
        int winningPossibility = 0;

        for(int i = 0; i <= time; i ++){
            speed = i;
            traveledDistance = speed * (time - i);

            if(traveledDistance > distanceToBeat) winningPossibility++;
        }

        sum *= winningPossibility;
    }

    std::cout << sum << std::endl;
}