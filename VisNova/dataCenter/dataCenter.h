#pragma once
#include <QObject>
#include "data.h"

namespace model
{


    class DataCenter : public QObject
    {
        Q_OBJECT
    public:
        explicit DataCenter(QObject *parent = nullptr);
        const KindAndTags* getkatPtr();
        static DataCenter* getInstance();
        ~DataCenter();


    private:
        static DataCenter* instance;
        KindAndTags* kat = nullptr;
    };
}
