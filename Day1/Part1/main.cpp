#include <iostream>
#include <fstream>
#include <string>

int main(){

    std::ifstream file("input.txt");

    std::string line;
    int sum = 0;

    for (std::string line; std::getline(file, line);){
        char first = ' ', last = ' ';
        //std::cout << line << std::endl;
        for(char c : line){
            if(isdigit(c)){
                if(first == ' ') first = c;
                else last = c;
            }
        }
        if(last == ' ') last = first;
        std::string sumStr = "";
        sumStr += first;
        sumStr += last;
        std::cout << sumStr << " : " << first << " : " << last << std::endl;
        sum += std::stoi(sumStr);
        
    }

    
    std::cout << sum << std::endl;
    return 0;
}