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
    std::vector<Range*> generateRangeFromRange(Range* range);

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

std::vector<Range*> Range::generateRangeFromRange(Range* range){
    std::vector<Range*> newRanges = {};

    if(begin >= range->getBegin() && end <= range->getEnd()){   
        long long b1 = range->getBegin();
        long long b2 = begin;
        long long b3 = end;

        newRanges.push_back(new Range(b1, b2 - 1, 0));
        newRanges.push_back(new Range(b2 + dist, b3 - 1 + dist, 0));
        newRanges.push_back(new Range(b3, range->getEnd(), 0));
    } else if(begin < range->getBegin() && end > range->getEnd()){
        newRanges.push_back(new Range(range->getBegin() + dist, range->getEnd() + dist, 0));
    } else if (begin < range->getBegin() && end <= range->getEnd()){
        long long b1 = range->getBegin();
        long long b2 = end;

        newRanges.push_back(new Range(b1 + dist, b2 - 1 + dist, 0));
        newRanges.push_back(new Range(b2,  range->getEnd(), 0));
    } else if (begin >= range->getBegin() && end > range->getEnd()){
        long long b1 = range->getBegin();
        long long b2 = begin;

        newRanges.push_back(new Range(b1, b2 - 1, 0));
        newRanges.push_back(new Range(b2 + dist,  range->getEnd() + dist, 0));
    } else {
        newRanges.push_back(range);
    }
    return newRanges;
}
