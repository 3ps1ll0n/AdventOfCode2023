#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>


template <class T>
using dMatrix = std::vector<std::vector<T>>;
template <class T>
using dVector = std::vector<T>;

struct Coordinate
{
    int xPos = 0;
    int yPos = 0;
    Coordinate(int x, int y):xPos(x), yPos(y){};
};


std::ostream& operator<<(std::ostream& os, dMatrix<char> m){
    for(auto v : m){
        os<<"\n";
        for(auto c : v) os << c;
    }
    return os;
}

dMatrix<char> init(std::string inputFile){
    dMatrix<char> pipes = {};
    std::ifstream input(inputFile);

    for(std::string line; std::getline(input, line);){
        pipes.push_back({});
        for(char c : line)
            pipes.at(pipes.size() - 1).push_back(c);
        
    }

    return pipes;
}

void getStartingPosition(dMatrix<char> pipesInput, int* setXPos, int* setYPos){
    for(int i = 0; i < pipesInput.size(); i++){
        for(int j = 0; j < pipesInput.at(i).size(); j++){
            if(pipesInput.at(i).at(j) == 'S'){
                *setXPos = j;
                *setYPos = i;
                return;
            }
        }
    }
}

inline void updateCurrentValue(char* pipe, int* x, int* y, char newPipe, int newX, int newY){
    *pipe = newPipe;
    *x = newX;
    *y = newY;
}

dMatrix<int> calculateLoopPos(dMatrix<char> pipesInput){
    dMatrix<int> coordinates(pipesInput.size());
    int currentX = 0;
    int currentY = 0;
    int beforeX = 0;
    int beforeY = 0;
    char currentPipe = 'S';

    getStartingPosition(pipesInput, &currentX, &currentY);
    coordinates.at(currentY).push_back(currentX);
    do{
        char right = currentX + 1 < pipesInput.at(0).size() ? pipesInput.at(currentY).at(currentX + 1) : 0;
        char left = currentX - 1 >= 0 ? pipesInput.at(currentY).at(currentX - 1) : 0;
        char up = currentY - 1 >= 0 ? pipesInput.at(currentY - 1).at(currentX) : 0;
        char down = currentY + 1 < pipesInput.size() ? pipesInput.at(currentY + 1).at(currentX) : 0;
        switch (pipesInput.at(currentY).at(currentX))
        {
        case 'S':
            beforeX = currentX;
            beforeY = currentY;
            if(up ==  '|' || up == '7' || up == 'F') updateCurrentValue(&currentPipe, &currentX, &currentY, up, currentX, currentY - 1);
            else if(down == '|' || down == 'L' || down == 'J') updateCurrentValue(&currentPipe, &currentX, &currentY, down, currentX, currentY + 1);
            else if(right == '-' || right == 'J' || right == '7' ) updateCurrentValue(&currentPipe, &currentX, &currentY, right, currentX + 1, currentY);
            else if(left == '-' || left == 'L' || left == 'F') updateCurrentValue(&currentPipe, &currentX, &currentY, left, currentX - 1, currentY);
            break;
        case '|':
            if(beforeY == currentY-1){
                beforeY = currentY;
                beforeX = currentX;
                updateCurrentValue(&currentPipe, &currentX, &currentY, down, currentX, currentY + 1); //Next Pipe Down
            }  
            else if (beforeY == currentY+1){
                beforeY = currentY;
                beforeX = currentX;
                updateCurrentValue(&currentPipe, &currentX, &currentY, up, currentX, currentY - 1); //Next Pipre Up
            } 
            break;    
        case '-':
            if(beforeX == currentX - 1){
                beforeX = currentX;
                beforeY = currentY;
                updateCurrentValue(&currentPipe, &currentX, &currentY, right, currentX + 1, currentY); //Next Pipe Right
            }
            else if(beforeX == currentX + 1){
                beforeX = currentX;
                beforeY = currentY;
                updateCurrentValue(&currentPipe, &currentX, &currentY, left, currentX - 1, currentY); //Next Pipe Left
            }
            break; 
        case 'L':
            if(beforeX == currentX + 1){
                beforeY = currentY;
                beforeX = currentX;
                updateCurrentValue(&currentPipe, &currentX, &currentY, up, currentX, currentY - 1); //Next Pipe Up
            }
            else if(beforeY == currentY - 1){
                beforeX = currentX;
                beforeY = currentY;
                updateCurrentValue(&currentPipe, &currentX, &currentY, right, currentX + 1, currentY); //Next Pipe Right
            }
            break;
        case 'J':
            if(beforeX == currentX - 1){
                beforeY = currentY;
                beforeX = currentX;
                updateCurrentValue(&currentPipe, &currentX, &currentY, up, currentX, currentY - 1); //Next Pipe Up
            }           
            else if(beforeY == currentY - 1){
                beforeX = currentX;
                beforeY = currentY;
                updateCurrentValue(&currentPipe, &currentX, &currentY, left, currentX - 1, currentY); //Next Pipe Left
            }
            break;
        case '7':
            if(beforeX == currentX - 1){
                beforeY = currentY;
                beforeX = currentX;
                updateCurrentValue(&currentPipe, &currentX, &currentY, down, currentX, currentY + 1); //Next Pipe Down
            }
            else if(beforeY == currentY + 1){
                beforeX = currentX;
                beforeY = currentY;
                updateCurrentValue(&currentPipe, &currentX, &currentY, left, currentX - 1, currentY); //Next Pipe Left
            }
            break;
        case 'F':
            if(beforeX == currentX + 1){
                beforeY = currentY;
                beforeX = currentX;
                updateCurrentValue(&currentPipe, &currentX, &currentY, down, currentX, currentY + 1); //Next Pipe Down
            }
            else if(beforeY == currentY + 1){
                beforeX = currentX;
                beforeY = currentY;
                updateCurrentValue(&currentPipe, &currentX, &currentY, right, currentX + 1, currentY); //Next Pipe Right
            }
            break;    
        default:
            std::cout << "WRONG CHAR" << std::endl;
            break;
        }
        //std::cout << currentX << " : " << currentY << " : " << currentPipe << std::endl;
        coordinates.at(currentY).push_back(currentX);
    }while(currentPipe != 'S'); 
    return coordinates;
}

bool findInVector(dVector<int> v, int value){
    for(int i : v)
        if(value == i) return true;
    return false;    
}

void drawLoop(dMatrix<int> coordinates){
    for(int i = 0; i < coordinates.size(); i++){
        for(int j = 0; j < coordinates.size(); j++){
            if(findInVector(coordinates.at(i), j)) std::cout << "@";
            else std::cout << " ";
        }
        std::cout << std::endl;
    }
}

dMatrix<char> convertCoordinatesToMap(dMatrix<int> coordinates){
    dMatrix<char> map = {};
    for(int i = 0; i < coordinates.size(); i++){
        for(int j = 0; j < coordinates.size(); j++){
            if(findInVector(coordinates.at(i), j)) map.at(i).push_back('1');
            else map.at(i).push_back('0');
        }
        std::cout << std::endl;
    }
    return map;
}

int calculateTrapsTiles(dMatrix<int> coordinates){
    int trapTils = 0;

    drawLoop(coordinates);

    for(dVector<int> vInt : coordinates){
        std::sort(vInt.begin(), vInt.end());
        //std::cout << vInt.size() << std::endl;
        for(int i = 1; i < vInt.size(); i+=2){
            trapTils += (vInt.at(i) - vInt.at(i - 1) - 1);
        }
    }

    return trapTils;
}