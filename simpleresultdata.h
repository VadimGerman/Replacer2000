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

struct SimpleReplaceData : public SearchData
{
    QQueue<int> *indexes;
};

struct RegExpReplaceData : public SearchData
{
    QQueue<QPair<int, QString> > *indexes;
};

struct SimpleResultData : public SearchData
{
    QMap<QString, QQueue<int>> *files;
};

struct RegExpResultData : public SearchData
{
    /// TODO.
};

#endif // SIMPLERESULTDATA_H
