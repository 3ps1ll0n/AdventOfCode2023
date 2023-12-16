#include "functions.hpp"

int main(){
    dMatrix<char> pipes = init("input.txt");
    //std::cout << pipes << std::endl;
    std::cout << calculateTrapsTiles(calculateLoopPos(pipes));
}