#pragma once

#include <string>
#include <vector>

class ScratchCard
{
private:
    std::vector<int> winingNumbers;
    std::vector<int> gotNumbers;
    int amount;
public:
    ScratchCard(std::vector<int> winingNumbers, std::vector<int> gotNumbers);
    ~ScratchCard();
    std::vector<int> getWiningNumbers(){return winingNumbers;};
    std::vector<int> getGotNumbers(){return gotNumbers;};
    int getAmount(){return amount;};
    void incrementAmount(int incrementation){amount+=incrementation;};\
};

ScratchCard::ScratchCard(std::vector<int> winingNumbers, std::vector<int> gotNumbers)
: winingNumbers(winingNumbers), gotNumbers(gotNumbers), amount(1){}

ScratchCard::~ScratchCard()
{
}