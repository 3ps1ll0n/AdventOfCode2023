#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "ScratchCard.hpp"

template <class T>
using dVector = std::vector<T>;
template <class T>
using dMatrix = dVector<dVector<T>>;

dVector<ScratchCard*> scratchCards;

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

int searchWiningNumbers(ScratchCard* card){
    int sameNbre = 0;
    for(int nbre1 : card->getWiningNumbers()){
        for(int nbre2 : card->getGotNumbers()){
            if(nbre1 == nbre2){
                sameNbre++;
                break;
            }
        }
    }
    return sameNbre;

}

void initScratchCards(dMatrix<std::string> strInput){

    for(dVector<std::string> line : strInput){
        
        dVector<int> winingNumbers = strToIntForVector(split(line.at(0), " "));
        dVector<int> gotNumbers = strToIntForVector(split(line.at(1), " "));
        ScratchCard* card = new ScratchCard(winingNumbers, gotNumbers);
        scratchCards.push_back(card);
    }
}

int calculAllScatchCards(){
    for(int i = 0; i < scratchCards.size(); i++){ // Repeat over all card numbers
        ScratchCard* card = scratchCards.at(i);
        int won = searchWiningNumbers(card);
        for(int k = 1; k <= won; k++){ //Depending od wich card you've won
            if((i + k) < scratchCards.size()) scratchCards.at(i+k)->incrementAmount(card->getAmount());
            //std::cout << i << " : " << k << std::endl;
        }
    }

    int sum = 0;

    for(ScratchCard* card : scratchCards)
        sum += card->getAmount();

    return sum;    
}

int main(){
    std::ifstream input("input.txt");
    dMatrix<std::string> strInput = {} ;
    for(std::string line; std::getline(input, line);){
        line.erase(0, line.find(": ") + 2);
        strInput.push_back(split(line, " | "));
        //std::cout << line << std::endl;
    }
    initScratchCards(strInput);
    std::cout << calculAllScatchCards() << std::endl;
}