#ifndef SIMPLEREPLACE_H
#define SIMPLEREPLACE_H

#include "simpleresultdata.h"

class SimpleReplace
{
public:
    SimpleReplace() = delete;
    static void replace(SimpleReplaceData &vars, QString &dataStr);
};

#endif // SIMPLEREPLACE_H
