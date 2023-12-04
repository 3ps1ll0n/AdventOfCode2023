#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::pair<std::string, int> color[] = {
    std::make_pair("green", 13),
    std::make_pair("blue", 14),
    std::make_pair("red", 12)
};

std::ostream& operator<<(std::ostream &os, const std::vector<std::string> strArr){
    os << "[\n";

    for(std::string str : strArr)
        os << str << "\n";
    os << "]";

    return os;
}

void operator+=(std::vector<std::string>& first, const std::vector<std::string>& toAdd){
    for(std::string str : toAdd)  
        first.push_back(str);
}


std::vector<std::string> split(std::string strToSplit, std::string spliter){
    std::vector<std::string> splitedStr = {};

    int beginingIndex = 0, endingIndex = 0;
    while((endingIndex = strToSplit.find(spliter)) != -1){
        splitedStr.push_back(
            strToSplit.substr(beginingIndex, endingIndex)
        );
        strToSplit.erase(beginingIndex, endingIndex + spliter.length());
        //std::cout << strToSplit << std::endl;
    }
    splitedStr.push_back(strToSplit);
    return splitedStr;
}

std::vector<std::string> split(std::vector<std::string> allStrToSplit, std::string spliter){
    std::vector<std::string> resultStr = {};

    for(std::string str : allStrToSplit){
        resultStr += split(str, spliter);
    }
    return resultStr;
}

bool isValidSet(std::string line){
    std::vector<std::string> all = {};
    all += split(split(line, "; "), ", ");

    for(std::string str : all){
        std::cout << str << std::endl;
        std::vector<std::string> params = split(str, " ");
        int nbreCube = std::stoi(params.at(0));
        std::string cubeColor = params.at(1);
        
        for(int i = 0; i < 3; i++){
            if(cubeColor == color[i].first && nbreCube > color[i].second) return false;
        }
    }
    return true;

}

int main(){

    std::ifstream input("input.txt");
    int i = 1;
    int sum = 0;
    
    for(std::string line; std::getline(input, line); i++){
        line.erase(0, line.find(": ") + 2);
        if(isValidSet(line)) sum += i;
    }
    
    std::cout << sum << std::endl;

    return 0;
}

