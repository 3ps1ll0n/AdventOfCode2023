#pragma once

#include <vector>
#include <string>

template <class T>
std::ostream& operator <<(std::ostream& os, std::vector<T> v){
    os << "[\n";
    for(T elem : v) os << v << "\n";
    os << "]\n";
    return os;
}

std::vector<std::string> split(std::string line, std::string splitter){
    std::vector<std::string> splittedString = {};
    int i = 0;
    while ((i = line.find(splitter)) != std::string::npos)
    {
        splittedString.push_back(line.substr(0, i));
        line.erase(0, i + splitter.size());
    }
    splittedString.push_back(line);
    return splittedString;
}