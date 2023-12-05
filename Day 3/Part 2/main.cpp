#include <iostream>
#include <fstream>
#include <string>
#include <vector>

template <class T>
using dVector = std::vector<T>;
template <class T>
using dMatrix = dVector<dVector<T>>;

struct Data
{
    int number;
    int xPos;
    int yPos;
    int length;

    bool isInRange(int x){return (x >= xPos && x <= (xPos + length - 1));}
};


dMatrix<char> machine {};
dVector<Data*> dataSet = {};
int sum = 0;

std::ostream& operator<<(std::ostream& os, const dMatrix<char> matrix){

    for(dVector<char> vector : matrix){
        for(char c : vector){
            os << c;
        }
        os << "\n";
    }

    return os;
}

void initMachine(){
    std::ifstream input("input.txt");

    for(std::string line; std::getline(input, line);){
        dVector<char> machineLine = {};
        for(char c : line){
            machineLine.push_back(c);
        }
        machine.push_back(machineLine);
    }
}

void initDataset(){
    std::string nbre = "";

    for(int i = 0; i < machine.size(); i++){
        for(int j = 0; j < machine.at(i).size(); j++){
            char c = machine.at(i).at(j);
            if(isdigit(c)){
                nbre += c;
                int posOfNextDigit = 1;
                char nextDigit = 0;
                while(j + posOfNextDigit < machine.at(i).size() && isdigit(nextDigit = machine.at(i).at(j + posOfNextDigit))){
                    nbre += nextDigit;
                    posOfNextDigit++;
                }
                Data* newData = new Data();// = new Data(std::stoi(nbre), j, i, (int)nbre.size());
                std::cout << nbre << std::endl;
                newData->number = std::stoi(nbre);
                newData->xPos = j;
                newData->yPos = i;
                newData->length = nbre.size();

                dataSet.push_back(newData);
                nbre = "";
                j += posOfNextDigit;
            }
        }
    }
}

int isGearValid(int xPos, int yPos){
    int left = (xPos - 1 >= 0) ? (xPos - 1) : 0;
    int right = (xPos + 1 < machine.at(0).size()) ? xPos + 1 : 0;
    /*int up = (yPos - 1 >= 0) ? (yPos -1) : 0;
    int down = (yPos + 1 < machine.size()) ? yPos + 1 : 0;*/

    dVector<Data*> valideData = {};

    for(Data* data : dataSet){
        if(data->yPos <= yPos + 1 && data->yPos >= yPos - 1){
            if(
                data->isInRange(xPos) ||
                data->isInRange(left) ||
                data->isInRange(right)
            ){
                valideData.push_back(data);
            }
        }
    }
    if(valideData.size() != 2) return 0;

    int power = 1;

    for(Data* data : valideData){
        power *= data->number;
    }
    return power;
}

void calculateValideNumbers(){
    for(int i = 0; i < machine.size(); i++){
        for(int j = 0; j < machine.at(i).size(); j++){
            char c = machine.at(i).at(j);
            if(c == '*'){
                sum += isGearValid(j, i);
            }
        }
    }
}

int main(){
    
    initMachine();
    initDataset();
    calculateValideNumbers();

    //std::cout << machine << std::endl;
    std::cout << "\n" << sum << std::endl;
    
}