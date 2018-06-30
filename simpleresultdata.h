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

struct ReplaceData : public SearchData
{
    QQueue<int> *indexes;
};

struct SimpleResultData : public SearchData
{
    QMap<QString, QQueue<int>> *files;
};

struct RXResultData : public SearchData
{
    /// TODO.
};

#endif // SIMPLERESULTDATA_H
