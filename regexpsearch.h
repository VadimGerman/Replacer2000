#ifndef REGEXPSEARCH_H
#define REGEXPSEARCH_H

#include <QString>
#include <QRegExp>

#include "simpleresultdata.h"

class RegExpSearch
{
    QRegExp m_needle;
    QStringView m_replacement;
    QString &m_data;
    QQueue<QPair<int, QString> > *m_foundIndexes;

public:
    RegExpSearch() = delete;

    RegExpSearch(SearchData *inData_,
                 QString &data, bool caseSensetive);

    ~RegExpSearch();

    QQueue<QPair<int, QString> > *search();

    QString &replace();

    // QString &quickReplace();
};

#endif // REGEXPSEARCH_H
