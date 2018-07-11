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
    SimpleSearch();         /// TODO: = delete.

    SimpleSearch(SearchData *inData_,
                 QString &data_,
                 bool ignoreWS_);

    virtual ~SimpleSearch();

    // Использует реализацию метода КМП.
    QQueue<int> *search();
};

//-----------------------------------------------------------------------------

template<typename _CmpCharT>
QVector<int> *SimpleSearch<_CmpCharT>::prefixFunction()
{
    QVector<int> *pFunction =
            new QVector<int>;
    pFunction->resize(m_needle.length());
//    pFunction[0] = 0;
    pFunction->data()[0] = 0;           /// TODO: That's ok?!

    for (int current = 1; current < m_needle.length(); ++current)
    {
        int matchedPrefix = current - 1;
        int candidate = pFunction->at(matchedPrefix);

        while (candidate != 0 && !_CmpCharT::eq(m_needle[current],
                                                m_needle[candidate]))
        {
            matchedPrefix = pFunction->at(matchedPrefix - 1);
            candidate = pFunction->at(matchedPrefix);
        }

        if (candidate == 0)
        {
            pFunction->data()[current] = !_CmpCharT::eq(m_needle[current],
                                                m_needle[0]) ? 1 : 0;
        }
        else
        {
            pFunction->data()[current] = candidate + 1;
        }
    }

    return pFunction;
}

template<typename _CmpCharT>
void SimpleSearch<_CmpCharT>::kmpSearch()
{
    // Получение префикс-функции и вспомогательных переменных.
    m_findIndexes = new QQueue<int>;
    QVector<int> *pFuntion = prefixFunction();
    int matchedP = 0;

    for (int current = 0; current < m_data.size(); ++current)
    {
        // Ignore white spaces.
        if (m_ignoreWhiteSpaces && m_data[current] == ' ')
            continue;

        // Сравнение при помощи класса переданного как аргумент
        // шаблона, реализующий операции для сравнения строк.
        // Взял эту идею из std::string. На этапе компиляции создаются
        // все нужные классы и я выигрыва в производительности одну
        // проверку if(case sensetive/insensetive)! (лол, сильно).
        if (_CmpCharT::eq(m_data[current], m_needle[matchedP]))
        {
            if (matchedP == m_needle.size() - 1)      // Нашли строку!
            {
                // matchedP шагов назад было удачное
                // вхождение подстроки в строку. Добавляем.
                m_findIndexes->push_back(abs(current - matchedP));
                matchedP = 0;
                continue;                       // Отлично, ищем дальше.
            }
            ++matchedP;
        }
        else if (matchedP != 0)
        {
            --current;
            matchedP = pFuntion->at(matchedP - 1);
        }
    }

    delete pFuntion;
}

template<typename _CmpCharT>
SimpleSearch<_CmpCharT>::SimpleSearch()
{
}

template<typename _CmpCharT>
SimpleSearch<_CmpCharT>::SimpleSearch(SearchData *inData_, QString &data_, bool ignoreWS_) :
    m_needle(inData_->needle),
    m_replacement(inData_->replacement),
    m_data(data_),
    m_ignoreWhiteSpaces(ignoreWS_),
    m_findIndexes(nullptr)
{
}

template<typename _CmpCharT>
SimpleSearch<_CmpCharT>::~SimpleSearch()
{

}

template<typename _CmpCharT>
QQueue<int> *SimpleSearch<_CmpCharT>::search()
{
    kmpSearch();
    return m_findIndexes;
}

#endif // SIMPLESEARCH_H
