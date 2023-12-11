#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

template <class T>
using dVector = std::vector<T>;
template <class T>
using dMatrix = dVector<dVector<T>>;

dVector<std::string> split(std::string &strToSplit, std::string spliter){
    dVector<std::string> splitedStr = {};
    int indexOfSpliter = 0;
    while((indexOfSpliter = strToSplit.find(spliter)) != std::string::npos){
        std::string subStr(strToSplit.substr(0, indexOfSpliter));
        if(!subStr.empty())splitedStr.push_back(strToSplit.substr(0, indexOfSpliter));
        strToSplit.erase(0, indexOfSpliter + spliter.size());
    }
    splitedStr.push_back(strToSplit);
    return splitedStr;
}

dVector<long long> strToIntForVector(dVector<std::string> vectorToConvert){
    dVector<long long> convertedVector = {};

    for(std::string line : vectorToConvert){
        convertedVector.push_back(std::stoll(line));
    }

    return convertedVector;
}

template <class T>
void append(std::vector<T>* iniVector, const std::vector<T> toAddVector){
    for(T element : toAddVector){
        iniVector->push_back(element);
    }
}

template <class T>
std::ostream& operator<<(std::ostream& os, std::vector<T> vector){
    os<< "[\n";

    for(T element : vector){
        os << element << "\n";
    }
    os << "]\n";

    return os;
}

long long displaySmaller(std::vector<long long> v){
    long long smallest = LLONG_MAX;

    //std::cout << v << std::endl;

    for(auto nbre : v){
        if(nbre < smallest) smallest = nbre;
    }
    std::cout << "Smallest : " << smallest << std::endl;
    return smallest;
}

