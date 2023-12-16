#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <fstream>



template <class T>
using dMatrix = std::vector<std::vector<T>>;
template <class T>
using dVector = std::vector<T>;

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

int calculateLoopSize(dMatrix<char> pipesInput){
    int loopSize = 0;
    int currentX = 0;
    int currentY = 0;
    int beforeX = 0;
    int beforeY = 0;
    char currentPipe = 'S';

    getStartingPosition(pipesInput, &currentX, &currentY);
    
    do{
        loopSize++;
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
        std::cout << currentX << " : " << currentY << " : " << currentPipe << std::endl;
    }while(currentPipe != 'S'); 
    loopSize++;
    return loopSize/2;
}