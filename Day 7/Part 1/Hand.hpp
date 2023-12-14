#pragma once

#include <string>
#include <vector>
#include <map>

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

    for(char c : hand){
        if(cardCout.find(c) == cardCout.end()) cardCout.insert(std::pair(c, 1));
        else cardCout.find(c)->second += 1;
    }

    if(cardCout.size() == 5) handType = HighCard;
    else if(cardCout.size() == 1) handType = FiveOfKind;
    else if(cardCout.size() == 2){
        for(std::map<char, int>::iterator it = cardCout.begin(); it != cardCout.end(); ++it){
            if(it->second == 4) {handType = FourOfKind; break;}
            else handType = FullHouse;
        }
    } 
    else if(cardCout.size() == 3) {
        for(std::map<char, int>::iterator it = cardCout.begin(); it != cardCout.end(); ++it){
            if(it->second == 3) {handType = ThreeOfKind; break;}
            else handType = TwoPair;
        }
    }
    else if(cardCout.size() == 4) handType = OnePair;

    return handType;
}
