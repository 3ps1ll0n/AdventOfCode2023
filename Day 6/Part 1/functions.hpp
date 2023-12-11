#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Race{
    int time;
    int distance;
    Race(int t, int d): time(t), distance(d){}
};

std::ostream& operator<<(std::ostream& os, std::vector<Race*> races){
    os << "[\n";

    for(Race* race : races){
        os << race->time << " : " << race->distance << std::endl;
    }

    os << "]";

    return os;
}

std::vector<int> seekNbreInLine(std::string line){
    std::vector<int> nbre = {};
    std::string currentNbre = "";

    for(int i = 0; i < line.size(); i++){
        char c = line.at(i);
        if(isdigit(c)) currentNbre+=c;
        else if(!currentNbre.empty()){
            nbre.push_back(stoi(currentNbre));
            currentNbre = "";
        }
        if((i == line.size() - 1) && !currentNbre.empty()) nbre.push_back(stoi(currentNbre));
    }
    std::cout << nbre.size() << std::endl;
    return nbre;
}

void init(std::vector<Race*>* races){
    std::ifstream input("input.txt");

    std::vector<int> times = {};
    std::vector<int> distances = {};

    std::string line;

    std::getline(input, line);
    //line.erase(0, line.find(": ") + 2);
    times = seekNbreInLine(line);

    std::getline(input, line);

    distances = seekNbreInLine(line);

    if(times.size() != distances.size() && times.size() != 0){
        std::cout << "INVALID INPUT FILE !" << std::endl;
        return;
    } else {
        std::cout << "VALID INPUT FILE !" << std::endl;
        
        for(int i = 0; i < times.size(); i++){
            races->push_back(new Race(times.at(i), distances.at(i)));
        }
    }


}

