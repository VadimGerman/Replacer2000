#ifndef SIMPLEREPLACE_H
#define SIMPLEREPLACE_H

#include "simpleresultdata.h"

class SimpleReplace
{
public:
    SimpleReplace() = delete;
    static void replace(ReplaceData &vars, QString &dataStr);
};

#endif // SIMPLEREPLACE_H
