#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

#include "Hand.hpp"

char reformateChar(char c){
    switch (c)
    {
    case 'A':
        return 'Z';
    case 'K':
        return 'Y';
    case 'Q':
        return 'X';
    case 'J':
        return '1';
    case 'T':
        return 'W';       
    default:
        return c;
    }
}

std::string reformateString(std::string line){
    std::string str = "";
    for(char c : line) str.push_back(reformateChar(c));
    return str;
}
std::vector<Hand*> init(std::string inputFile){
    std::vector<Hand*> allHands = {};

    std::ifstream input(inputFile);

    for(std::string line; std::getline(input, line);){
        allHands.push_back(new Hand(reformateString(line.substr(0, 5)), std::stoi(line.substr(6, line.size()))));
    }

    return allHands;
}

std::ostream& operator<<(std::ostream& os, std::vector<Hand*> allHands){
    os << "[\n";
    for(Hand* hand : allHands){
        os << hand->getHand() << " : " << hand->getBid() << std::endl;
    }
    os << "]\n";

    return os;
}

void displayHandType(HandType handType){
    switch (handType)
    {
    case FiveOfKind:
        std::cout << "FiveOfKind";
        break;
    case FourOfKind:
        std::cout << "FourOfKind";
        break;
    case FullHouse:
        std::cout << "FullHouse";
        break;
    case ThreeOfKind:
        std::cout << "ThreeOfKind";
        break;    
    case TwoPair:
        std::cout << "TwoPair";
        break;
    case OnePair:
        std::cout << "OnePair";
        break;    
    case HighCard:
        std::cout << "HighCard";
        break;            
    default:
    std::cout << "VOID";
        break;
    }
}

template <class T>
void append(std::vector<T>* iniVector, std::vector<T> toAddVector){
    for(T elem : toAddVector){
        iniVector->push_back(elem);
    }
}

std::vector<std::string> retrieveAllCardSet(std::vector<Hand*> hands){
    std::vector<std::string> cards = {};
    for(Hand* hand : hands) cards.push_back(hand->getHand());
    return cards;
}

std::vector<Hand*> sortHands(std::vector<Hand*> hands){
    std::vector<Hand*> sortedHands = {};
    std::string label = "23456789TJQKA";
    std::map<HandType, std::vector<Hand*>> handSorter = {
        {FiveOfKind, {}},
        {FourOfKind, {}},
        {FullHouse, {}},
        {ThreeOfKind, {}},
        {TwoPair, {}},
        {OnePair, {}},
        {HighCard, {}}
    };

    std::map<std::string, int> allHandsValue;

    for(auto hand : hands){
        //displayHandType(hand->getHandType());
        handSorter.find(hand->getHandType())->second.push_back(hand);
        allHandsValue.insert(std::pair(hand->getHand(), hand->getBid()));
    }

    for(std::map<HandType, std::vector<Hand*>>::iterator it = handSorter.begin(); it != handSorter.end(); ++it){
        std::vector<std::string> handSet = retrieveAllCardSet(it->second);

        std::sort(handSet.begin(), handSet.end());
        
        for(std::string str : handSet) {
            sortedHands.push_back(new Hand(str, allHandsValue.find(str)->second));
            Hand* h = sortedHands.at(sortedHands.size() - 1);
            std::cout << "\n" << h->getHand() << " : ";
            displayHandType(h->getHandType());
            std::cout << " : " << h->getBid() << std::endl;
        }
    }

    return sortedHands;
}

long long totalWinning(std::vector<Hand*> hands){
    long long sum = 0;
    for(int i = 0; i < hands.size(); i++){
        //long long formerSome = sum;
        sum += (hands.at(i)->getBid()*(i+1));
        //std::cout << sum << " = " << formerSome << " + " << hands.at(i)->getBid() << " * " << (i+1) << std::endl;
    }
    
    return sum;
}