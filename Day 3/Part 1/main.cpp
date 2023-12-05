#include <iostream>
#include <fstream>
#include <string>
#include <vector>

template <class T>
using dVector = std::vector<T>;
template <class T>
using dMatrix = dVector<dVector<T>>;

dMatrix<char> machine {};
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

void calculateValideNumbers(){
    std::vector<std::pair<int, int>> nbreCoordinates = {};

    for (int i = 0; i < machine.size(); i++){
        for(int j = 0; j < machine.at(i).size(); j++){
            char c = machine.at(i).at(j);
            if(isdigit(c)){
                nbreCoordinates.push_back(std::make_pair(i, j));
                int k = 1; 
                while(j + k < machine.at(i).size() && isdigit(machine.at(i).at(j + k))){
                    nbreCoordinates.push_back(std::make_pair(i, j+k));
                    k++;
                }
                j += k;
            }
            for(int k = 0; k < nbreCoordinates.size(); k++){
                int left = (nbreCoordinates.at(k).second - 1 >= 0) ? (nbreCoordinates.at(k).second - 1) : 0;
                int right = (nbreCoordinates.at(k).second + 1 < machine.at(i).size()) ? nbreCoordinates.at(k).second + 1 : 0;
                int up = (nbreCoordinates.at(k).first - 1 >= 0) ? (nbreCoordinates.at(k).first -1) : 0;
                int down = (nbreCoordinates.at(k).first + 1 < machine.size()) ? nbreCoordinates.at(k).first + 1 : 0;
                int centeredX = nbreCoordinates.at(k).second;
                int centeredY = nbreCoordinates.at(k).first;

                if( 
                    (machine.at(centeredY).at(left) != '.' &&   !isdigit(machine.at(centeredY).at(left))) ||
                    (machine.at(up).at(left) != '.' &&          !isdigit(machine.at(up).at(left))) ||
                    (machine.at(up).at(centeredX) != '.' &&     !isdigit(machine.at(up).at(centeredX))) ||
                    (machine.at(up).at(right) != '.' &&         !isdigit(machine.at(up).at(right))) ||
                    (machine.at(centeredY).at(right) != '.' &&  !isdigit(machine.at(centeredY).at(right))) ||
                    (machine.at(down).at(right) != '.' &&       !isdigit(machine.at(down).at(right))) ||//
                    (machine.at(down).at(centeredX) != '.' &&   !isdigit(machine.at(down).at(centeredX))) ||//
                    (machine.at(down).at(left) != '.' &&        !isdigit(machine.at(down).at(left)))//
                ){
                    int nbre = 0;
                    std::string nbreStr = "";
                    for(int l = 0; l < nbreCoordinates.size(); l++){
                        centeredX = nbreCoordinates.at(l).second;
                        centeredY = nbreCoordinates.at(l).first;
                        nbreStr += machine.at(centeredY).at(centeredX);
                    }
                    nbre = std::stoi(nbreStr);
                    sum += nbre;   
                    break;
                }
            }
            nbreCoordinates.clear();
        }

    }
}

int main(){
    
    initMachine();
    calculateValideNumbers();

    std::cout << machine << std::endl;
    std::cout << "\n" << sum << std::endl;
    
}