#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

template <class T>
using dMatrix = std::vector<std::vector<T>>;
template <class T>
using dVector = std::vector<T>;

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

dMatrix<char> expandsUnivers(dMatrix<char> univers){
    dMatrix<char> expandedUnivers = {};
    int ofset = 0;

    for(int i = 0; i < univers.size(); i++){
        bool isEmpty = true;
        for(int j = 0; j < univers.at(i).size(); j++){
            if(univers.at(i).at(j) == '#') {
                expandedUnivers.push_back(univers.at(i));
                isEmpty = false;
                break;
            }
        }
        if(isEmpty) {
            expandedUnivers.push_back(std::vector(univers.at(i).size(), '.'));
            expandedUnivers.push_back(std::vector(univers.at(i).size(), '.'));
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
            for(int k = 0; k < expandedUnivers.size(); k++){
            dVector<char>* temp = &expandedUnivers.at(k);
            temp->insert(temp->begin() + i + ofset, '+');
            }
            ofset++;
        }
    }

    return expandedUnivers;
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

int sumOfDistances(dMatrix<char> univers){
    int sum = 0;
    int operartions = 0;

    dVector<Coordinates*> galaxiesPos = retrieveCoordinates(univers);
    std::cout << galaxiesPos.size() << " : " << univers.size()*univers.at(0).size() << std::endl;

    for(int i = 0; i < galaxiesPos.size() - 1; i++){
        Coordinates* g1 = galaxiesPos.at(i);
        //std::cout << g1->x << " : "<< g1->y << std::endl;
        for(int j = i + 1; j < galaxiesPos.size(); j++){
            Coordinates* g2 = galaxiesPos.at(j);
            int dX = abs(g2->x - g1->x);
            int dY = abs(g2->y - g1->y);
            sum += (dX + dY);
            
            operartions++;
        }
    }
    std::cout << "\nOperations count : " << operartions << std::endl;

    return sum;
}