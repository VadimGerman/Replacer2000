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
    int m_matchesCount;
    QList<int> *m_fIndexes;
    QStringView m_needle;
    QStringView m_replacement;
    QString m_data;
    bool m_ignoreWhiteSpaces;

    // Использует m_needle для составления префикс функции.
    QVector<int> *prefixFunction();

    // Ищет в m_data вхождения m_needle при помощи префикс функции.
    void kmpSearch();

public:
    SimpleSearch() = delete;

    SimpleSearch(QStringView &needle_,
                 QStringView &replacement_,
                 const QString &data_,
                 bool ignoreWS_ = false);

    SimpleSearch(SimpleResultData *inData_,
                 const QString &data_,
                 bool ignoreWS_ = false);

    virtual ~SimpleSearch();

    // Ignore white spaces.
    void setIgnoreWhiteSpaces(bool ignore_);
    bool getIgnoreWhiteSpaces() const;

    // Использует реализацию метода КМП.
    void search();

    void replace();

    // TODO: Следующие два метода заменить на возвращаемое
    // значение соответствующих методов.

    // После вызова search() можно узнать по каким индексам были
    // найдены вхождения.
    QList<int> *getFoundIndexes();
\
    // После вызова replace() вы скорее всего захотите получить
    // измененную строку.
    QString getChangedData() const;
};

#endif // SIMPLESEARCH_H
