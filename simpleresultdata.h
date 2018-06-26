#ifndef SIMPLERESULTDATA_H
#define SIMPLERESULTDATA_H

#include <QString>
#include <QQueue>
#include <QMap>

struct SearchData
{
    QStringView needle;
    QStringView replacement;
};

struct SimpleResultData
{
    QStringView needle;
    QStringView replacement;
    QMap<QString, QQueue<int>> *files;
};

#endif // SIMPLERESULTDATA_H
