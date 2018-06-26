#ifndef SIMPLESEARCH_H
#define SIMPLESEARCH_H

// Результатами работы класса являются 2 объекта.
// Первый - спписок найденных вхождений, заполняемый в search().


#include <QString>
#include <QVector>

#include "simpleresultdata.h"

template <typename _CmpCharT>
class SimpleSearch
{
private:
    QStringView m_needle;
    QStringView m_replacement;
    QString &m_data;
    QQueue<int> *m_findIndexes;

    bool m_ignoreWhiteSpaces;

    // Использует m_needle для составления префикс функции.
    QVector<int> *prefixFunction();

    // Ищет в m_data вхождения m_needle при помощи префикс функции.
    void kmpSearch();

public:
    SimpleSearch() = delete;

    SimpleSearch(SearchData *inData_,
                 QString &data_,
                 bool ignoreWS_ = false);

    virtual ~SimpleSearch();

    // Использует реализацию метода КМП.
    QQueue<int> *search();

    // Если ты вдруг потерял строку которую давал на входе -
    // не беспокойся, после замены вызовом replacement,
    // будет возвращена ссылка на неё.
    QString &replace();
};

#endif // SIMPLESEARCH_H
