#ifndef SIMPLERESULTDATA_H
#define SIMPLERESULTDATA_H

#include <QString>
#include <QQueue>

struct SimpleResultData
{
    QString needle;
    QString replacement;
    QQueue<int> indexes;
};

#endif // SIMPLERESULTDATA_H
