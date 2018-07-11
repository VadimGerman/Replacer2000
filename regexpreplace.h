#ifndef REGEXPREPLACE_H
#define REGEXPREPLACE_H

#include "simpleresultdata.h"

class RegExpReplace
{
public:
    RegExpReplace() = delete;
    static void replace(RegExpReplaceData &vars, QString &dataStr);
};

#endif // REGEXPREPLACE_H
