#include <iostream>
#include <fstream>
#include <string>
#include <regex>

const std::string allStrNbre[] = {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
};

void findNumberInString(std::string str, char &first, char &last){
    std::pair<char, int> f(0, INT_MAX), l(0, -1);
    f.second = str.find_first_of("123456789");
    if(f.second != std::string::npos) f.first = str.at(f.second);

    l.second = str.find_last_of("123456789");
    if(l.second != std::string::npos) l.first = str.at(l.second);

    for(int i = 0; i < sizeof(allStrNbre)/sizeof(allStrNbre[0]); i++){
        std::string word(allStrNbre[i]);
        int strIndex = -1;
        //std::cout << word << std::endl;
        if((strIndex = str.find(word)) != std::string::npos){
            if(strIndex < f.second) {
                f.second = strIndex;
                f.first = '1' + i;
            } else {
                do{
                    if(strIndex > l.second){
                        l.second = strIndex;
                        l.first = '1' + i;
                    }
                }while((strIndex = str.find(word, strIndex+1)) != std::string::npos);
            }
        }
    }

    if(f.second != std::string::npos) first = f.first;
    if(l.second != std::string::npos) last = l.first;

    //std::cout << first << " : " << last << std::endl;
}

int main(){

    std::ifstream file("input.txt");

    std::string line;
    int sum = 0;

    for (std::string line; std::getline(file, line);){
        char first = ' ', last = ' ';
        //std::cout << line << std::endl;
        
        findNumberInString(line, first, last);

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