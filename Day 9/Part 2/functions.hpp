#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


template <class T>
std::ostream& operator<<(std::ostream& os, std::vector<T> v){
    os << "[\n";

    for(T elem : v){
        os << elem << std::endl;
    }

    os << "]";

    return os;
}

template <class T>
inline void append(std::vector<T>* iniVector, std::vector<T> toAdd){
    for(T elem : toAdd)
        iniVector->push_back(elem);  
}

std::vector<std::string> split(std::string line, std::string splitter){
    std::vector<std::string> splittedString = {};
    int i = 0;
    while ((i = line.find(splitter)) != std::string::npos)
    {
        splittedString.push_back(line.substr(0, i));
        line.erase(0, i + splitter.size());
    }
    splittedString.push_back(line);
    return splittedString;
}

std::vector<int> stringToIntVector(std::vector<std::string> line){
    std::vector<int> numbers;

    for(std::string nbre : line){
        try{
            numbers.push_back(std::stoi(nbre));
        } catch(std::exception &err){
            std::cout << err.what() << std::endl;
        }
    }

    return numbers;
}

std::vector<std::vector <int>> init(std::string inputFile){
    std::vector<std::vector <int>> numbersSet = {};
    std::ifstream input(inputFile);

    for(std::string line; std::getline(input, line);){
        numbersSet.push_back({});
        int last = numbersSet.size() - 1;
        
        append(&numbersSet.at(last), stringToIntVector(split(line, " ")));
    }
    return numbersSet;
}

inline bool containsOnlyZero(std::vector<int> nbres){
    for(int n : nbres){
        if(n != 0) return false;
    }
    return true;    
}

int calculatePrediction(std::vector <int> nbreSet){
    int predictions = nbreSet.at(0);
    std::vector<std::vector <int>> gap = {};
    int last = 0;
    gap.push_back(nbreSet);
    

    do{
        gap.push_back({});
        last = gap.size() - 1;
        for(int i = 1; i < gap.at(last - 1).size(); i++)
            gap.at(last).push_back(gap.at(last - 1).at(i) - gap.at(last - 1).at(i- 1));
    }while(!containsOnlyZero(gap.at(last)));

    int lastResult;

    for(int i = gap.size() - 2; i >= 1; i--){
        if(i == gap.size() - 2)lastResult= gap.at(i).at(0) - gap.at(i + 1).at(0);
        else lastResult = gap.at(i).at(0) - lastResult;
    }
    predictions -= lastResult;
    return predictions;
}

int calculatePredictions(std::vector<std::vector <int>> nbreSets){
    int sum = 0;

    for(std::vector<int> nbreSet : nbreSets){
        sum += calculatePrediction(nbreSet);
    }

    return sum;
}

