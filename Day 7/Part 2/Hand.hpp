#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>

enum HandType{
    HighCard,
    OnePair,
    TwoPair,
    ThreeOfKind,
    FullHouse,
    FourOfKind,
    FiveOfKind,
    VOID
};

void displayHandType2(HandType handType);

class Hand
{
private:
    std::string hand;
    int bid;
public:
    Hand(std::string h, int b);
    ~Hand();
    HandType getHandType();

    std::string getHand(){return hand;};
    int getBid(){return bid;};
};

Hand::Hand(std::string h, int b)
: hand(h), bid(b){}

Hand::~Hand(){}

HandType Hand::getHandType(){
    HandType handType = VOID;
    std::map<char, int> cardCout;
    int jokerCount = 0;

    for(char c : hand){
        if(c == '1') jokerCount++;
        else if(cardCout.find(c) == cardCout.end()) cardCout.insert(std::pair(c, 1));
        else cardCout.find(c)->second += 1;
    }

    int size = cardCout.size();
    if(jokerCount != 0) size++;

    if(size == 1) handType = FiveOfKind;
    else if(size == 2){
        if(jokerCount >= 1) handType = FiveOfKind;
        else for(std::map<char, int>::iterator it = cardCout.begin(); it != cardCout.end(); ++it){
            if(it->second == 4) {handType = FourOfKind; break;}
            else handType = FullHouse;
        }
    } 
    else if(size == 3) {
        int highest = 0;
        for(std::map<char, int>::iterator it = cardCout.begin(); it != cardCout.end(); ++it){
            if(it->second > highest) highest = it->second;
        }

        if(highest + jokerCount == 3 && jokerCount >= 1) handType = FullHouse;
        else if(highest + jokerCount == 4) handType = FourOfKind;
        else if(highest == 2) handType = TwoPair;
        else if(highest == 3) handType = ThreeOfKind;

    }
    else if(size == 4) {
        int highest = 0;
        for(std::map<char, int>::iterator it = cardCout.begin(); it != cardCout.end(); ++it){
            if(it->second > highest) highest = it->second;
        }
        if(highest == 1 && jokerCount == 2) handType = ThreeOfKind;
        else if(highest == 2 && jokerCount == 1) handType = ThreeOfKind;
        else handType = OnePair;
    }
    else if(size == 5) {
        if(jokerCount == 0) handType = HighCard;
        else handType = OnePair;
    }

    //std::cout << "\n" << hand << " : " << jokerCount << " : ";
    //displayHandType2(handType);
    

    return handType;
}

void displayHandType2(HandType handType){
    switch (handType)
    {
    case FiveOfKind:
        std::cout << "FiveOfKind" << std::endl;
        break;
    case FourOfKind:
        std::cout << "FourOfKind" << std::endl;
        break;
    case FullHouse:
        std::cout << "FullHouse" << std::endl;
        break;
    case ThreeOfKind:
        std::cout << "ThreeOfKind" << std::endl;
        break;    
    case TwoPair:
        std::cout << "TwoPair" << std::endl;
        break;
    case OnePair:
        std::cout << "OnePair" << std::endl;
        break;    
    case HighCard:
        std::cout << "HighCard" << std::endl;
        break;            
    default:
    std::cout << "VOID" << std::endl;
        break;
    }
}
