#include <iostream>
#include <fstream>
#include <string>
#include <vector>

template <class T>
using dVector = std::vector<T>;
template <class T>
using dMatrix = dVector<dVector<T>>;

dMatrix<std::string> scratchCards = {};

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

inline int powerOf(int nbre, int power){
    if(power == 0) return 1;
    int total = nbre;
    for (int i = 1; i < power; i ++){
        total *= nbre;
    }
    return total;
}

dVector<int> strToIntForVector(dVector<std::string> vectorToConvert){
    dVector<int> convertedVector = {};

    for(std::string line : vectorToConvert){
        //std::cout << line << std::endl;
        convertedVector.push_back(std::stoi(line));
    }

    return convertedVector;
}

int calculateWiningNumbers(dVector<int> v1, dVector<int> v2){
    int sameNbre = 0;
    for(int nbre1 : v1){
        for(int nbre2 : v2){
            if(nbre1 == nbre2){
                sameNbre++;
                break;
            }
        }
    }
    if(sameNbre == 0) return 0;
    else return powerOf(2, sameNbre-1);
}

int calculatePoints(){
    int sum = 0;

    for(dVector<std::string> line : scratchCards){
        dVector<int> winingNumbers = strToIntForVector(split(line.at(0), " "));
        dVector<int> gotNumbers = strToIntForVector(split(line.at(1), " "));

        sum += calculateWiningNumbers(winingNumbers, gotNumbers);
    }

    return sum;
}

int main(){
    std::ifstream input("input.txt");

    for(std::string line; std::getline(input, line);){
        line.erase(0, line.find(": ") + 2);
        scratchCards.push_back(split(line, " | "));
        //std::cout << line << std::endl;
    }

    std::cout << calculatePoints() << std::endl;
}