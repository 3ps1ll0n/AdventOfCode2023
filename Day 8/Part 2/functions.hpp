#pragma once

#include <vector>
#include <string>

template <class T>
std::ostream& operator <<(std::ostream& os, std::vector<T> v){
    os << "[\n";
    for(T elem : v) os << elem << "\n";
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

typedef long long int ll;
 
// Utility function to find
// GCD of 'a' and 'b'
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
 
// Returns LCM of array elements
ll findlcm(std::vector<int> arr, int n)
{
    // Initialize result
    ll ans = arr[0];
 
    // ans contains LCM of arr[0], ..arr[i]
    // after i'th iteration,
    for (int i = 1; i < n; i++)
        ans = (((arr[i] * ans)) /
                (gcd(arr[i], ans)));
 
    return ans;
}