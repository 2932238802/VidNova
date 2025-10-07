#pragma once
#include <stdint.h>
#include <QString>
#include <random>



const inline QString CHARNUMBER = "qwertyuiopasdfghjklzxcvbnm1234567890-";

class Rand
{
    using rd = std::random_device;
public:
    static QString RandChars(int lenth);
    static int64_t RandNumber(int min_number = 0,int max_number = 0 );
    static std::mt19937 engine_;
};

