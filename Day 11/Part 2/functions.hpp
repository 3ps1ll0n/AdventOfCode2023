#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

template <class T>
using dMatrix = std::vector<std::vector<T>>;
template <class T>
using dVector = std::vector<T>;

std::vector<int> verticalExpensionPoint = {};
std::vector<int> horizontalExpensionPoint = {};

struct Coordinates{
    int x = 0;
    int y = 0;
    Coordinates(int xPos, int yPos):x(xPos), y(yPos){}
};

inline int abs(int value){
    return value < 0 ? -value : value;
}

std::ostream& operator<<(std::ostream& os, dMatrix<char> m){
    for(dVector<char> v : m){
        for(char c : v)
            os << c;
        os << "\n";
    }
    return os;
}

dMatrix<char> init(std::string inputFile){
    dMatrix<char> galaxies = {};
    std::ifstream input(inputFile);

    for(std::string line; std::getline(input, line);){
        galaxies.push_back({});
        int last = galaxies.size() - 1;
        for(char c : line){
            galaxies.at(last).push_back(c);
        }
    }
    return galaxies;
}

void findExpandationPoints(dMatrix<char> univers){
    for(int i = 0; i < univers.size(); i++){
        bool isEmpty = true;
        for(int j = 0; j < univers.at(i).size(); j++){
            if(univers.at(i).at(j) == '#') {
                isEmpty = false;
                break;
            }
        }
        if(isEmpty) {
            horizontalExpensionPoint.push_back(i);
        }
    }
    for(int i = 0; i < univers.at(0).size(); i++){
        bool isEmpty = true;
        for(int j = 0; j < univers.size(); j++){
            if(univers.at(j).at(i) == '#'){
                isEmpty = false;
                break;
            }
        }
        if(isEmpty){
            verticalExpensionPoint.push_back(i);
        }
    }
    std::cout << verticalExpensionPoint.size() << " : " << horizontalExpensionPoint.size() << std::endl;
}

dVector<Coordinates*> retrieveCoordinates(dMatrix<char> univers){
    dVector<Coordinates*> coo = {};
    for(int i = 0; i < univers.size(); i++){
        for(int j = 0; j < univers.at(i).size(); j++){
            if(univers.at(i).at(j) == '#')  coo.push_back(new Coordinates(j, i));
        }
    }
    return coo;
}

int isExpandationPointInRange(int x1, int x2, char verticaleOrHorizontale){
    int nbreOfExpentionPointsPass = 0;
    if(verticaleOrHorizontale == 'v'){
        for(int i : verticalExpensionPoint)
            if((i > x1 && i < x2) || (i > x2 && i < x1))nbreOfExpentionPointsPass++;
    } 
    else if(verticaleOrHorizontale == 'h'){
        for(int i :horizontalExpensionPoint)
            if((i > x1 && i < x2) || (i > x2 && i < x1))nbreOfExpentionPointsPass++;
    }

    return nbreOfExpentionPointsPass;
}

long long sumOfDistances(dMatrix<char> univers){
    long long sum = 0;
    int operartions = 0;

    dVector<Coordinates*> galaxiesPos = retrieveCoordinates(univers);
    std::cout << galaxiesPos.size() << " : " << univers.size()*univers.at(0).size() << std::endl;

    for(int i = 0; i < galaxiesPos.size() - 1; i++){
        Coordinates* g1 = galaxiesPos.at(i);
        for(int j = i + 1; j < galaxiesPos.size(); j++){
            Coordinates* g2 = galaxiesPos.at(j);
            int dX = abs(g2->x - g1->x);
            int dY = abs(g2->y - g1->y);
            sum += (dX + dY);

            sum += (isExpandationPointInRange(g2->x, g1->x, 'v') + isExpandationPointInRange(g2->y, g1->y, 'h'))*(1000000-1);
            
            operartions++;
        }
    }
    std::cout << "\nOperations count : " << operartions << std::endl;

    return sum;
}