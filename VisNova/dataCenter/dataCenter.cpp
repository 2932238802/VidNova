#include "dataCenter.h"

namespace model
{
    DataCenter* DataCenter::instance = nullptr;

    DataCenter::DataCenter(QObject *parent)
        : QObject{parent}
    {

    }

    const KindAndTags *DataCenter::getkatPtr()
    {
        if(kat == nullptr)
        {
            kat = new KindAndTags();
        }
        return kat;
    }

    DataCenter::~DataCenter()
    {
        delete kat;
    }

    DataCenter *DataCenter::getInstance()
    {
        if(instance == nullptr)
        {
            instance = new DataCenter();
        }
        return instance;
    }


}
