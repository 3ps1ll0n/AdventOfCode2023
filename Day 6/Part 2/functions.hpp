#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Race{
    long long time;
    long long distance;
    Race(long long t, long long d): time(t), distance(d){}
};

std::ostream& operator<<(std::ostream& os, std::vector<Race*> races){
    os << "[\n";

    for(Race* race : races){
        os << race->time << " : " << race->distance << std::endl;
    }

    os << "]";

    return os;
}

long long seekNbreInLine(std::string line){
    long long nbre = 0;
    std::string currentNbre = "";

    for(int i = 0; i < line.size(); i++){
        char c = line.at(i);
        if(isdigit(c)) currentNbre+=c;
        else if(!currentNbre.empty()){
        }
    }
    std::cout << currentNbre << std::endl;
    nbre = std::stoll(currentNbre);
    return nbre;
}

void init(Race** race){
    std::ifstream input("input.txt");

    long long time = 0;
    long long distance = 0;

    std::string line;

    std::getline(input, line);
    //line.erase(0, line.find(": ") + 2);
    time = seekNbreInLine(line);

    std::getline(input, line);

    distance = seekNbreInLine(line);

    std::cout << time << " : " << distance << std::endl;

   *race = new Race(time, distance);


}

