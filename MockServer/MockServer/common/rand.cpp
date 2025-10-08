#include "rand.h"


std::mt19937 Rand::engine_ = []{
    std::random_device rd;
    return std::mt19937(rd());
}();


QString Rand::RandChars(int lenth)
{
    std::uniform_int_distribution<int> valid_index(0,CHARNUMBER.size()-1);
    QString str;
    str.reserve(lenth);
    for(int i = 0; i < lenth ; i ++)
    {
        str += CHARNUMBER[valid_index(engine_)];
    }
    return str;
}

int64_t Rand:: RandNumber(int min_number,int max_number)
{
    if(min_number > max_number)
    {
        int tmp = min_number;
        min_number = max_number;
        max_number = tmp;
    }
    std::uniform_int_distribution<int> valid_index(min_number,max_number+1);
    return valid_index(engine_);
}


