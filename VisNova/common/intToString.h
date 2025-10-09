#pragma once

#include <QString>

static QString intToString(int value)
{
    if(value < 10000)
    {
        return QString::number(value);
    }
    else{
        return QString::asprintf("%.1lf万",value/10000.0);
    }
}

static QString intToString_2(int value)
{
    if(value < 10000)
    {
        return QString::number(value);
    }
    else{
        return QString::asprintf("%.2lfw",value/10000.0);
    }
}
