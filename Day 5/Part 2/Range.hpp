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
    bool isRangeInRange(Range* otherRange);

    long long getBegin(){return begin;};
    long long getDist(){return dist;};
    long long getEnd(){return end;};
};

Range::Range(long long begining, long long ending, long long distance)
:begin(begining), end(ending), dist(distance){};

Range::~Range(){}

bool Range::isRangeInRange(Range* otherRange){
    if(otherRange->getBegin() <= end && otherRange->getBegin() >= begin) return true;
    if(otherRange->getEnd() <= end && otherRange->getEnd() >= begin) return true;
    return false;
}
