#include "Map.hpp"


int main(){
    Map* map = new Map();
    map->init("input.txt");
    std::cout << map->calculateStepsGhost() << std::endl;
}