#include "rand.h"

QString Rand::RandChars(int lenth)
{
    rd r_d;
    std::mt19937 engine(r_d());
    std::uniform_int_distribution<int> valid_index(0,CHARNUMBER.size()-1);
    QString str;
    str.reserve(lenth);
    for(int i = 0; i < lenth ; i ++)
    {
        str += CHARNUMBER[valid_index(engine)];
    }
    return str;
}

int64_t Rand::RandNumber(int lenth)
{
    if(lenth >= 10) lenth = 10;
    rd r_d;
    std::mt19937 engine(r_d());
    std::uniform_int_distribution<int> valid_index(0,10);
    int sum = 0 ;
    for(int i =0 ; i < lenth ; i++)
    {
        sum*=10;
        sum += valid_index(engine);
    }
    return sum;
}


