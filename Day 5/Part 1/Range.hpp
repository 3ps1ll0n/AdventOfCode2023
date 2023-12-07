#pragma once

class Range
{
private:
    long long begin;
    long long end;
    long long dist;
public:
    Range(long long begining, long long ending, long long distance);
    ~Range();
    bool isInRange(long long nbre){return nbre >= begin && nbre <= end;};
    long long convertNbre(long long nbre){return nbre + dist;};
};

Range::Range(long long begining, long long ending, long long distance)
:begin(begining), end(ending), dist(distance){};

Range::~Range()
{
}
