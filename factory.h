#ifndef FACTORY_H
#define FACTORY_H

#include <QString>

#include "simplesearch.h"

class Factory
{
public:
    static SimpleSearch *createSearch(const QString &type);
};

#endif // FACTORY_H
