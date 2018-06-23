#include "simplesearch.h"

template<typename _CmpCharT>
SimpleSearch<_CmpCharT>::SimpleSearch(QStringView &needle_,
                                      QStringView &replacement_,
                                      const QString &data_,
                                      bool ignoreWS_) :
        m_needle(needle_),
        m_replacement(replacement_),
        m_data(data_),
        m_ignoreWhiteSpaces(ignoreWS_),
        m_fIndexes(new QList<int>)
{

}

template<typename _CmpCharT>
SimpleSearch<_CmpCharT>::SimpleSearch(SimpleResultData *inData_,
                                      const QString &data_,
                                      bool ignoreWS_) :
    m_needle(inData_->needle),
    m_replacement(inData_->replacement),
    m_data(data_),
    m_ignoreWhiteSpaces(ignoreWS_),
    m_fIndexes(new QList<int>)
{

}

template<typename _CmpCharT>
SimpleSearch<_CmpCharT>::~SimpleSearch()
{

}

template<typename _CmpCharT>
void SimpleSearch<_CmpCharT>::setIgnoreWhiteSpaces(bool ignore_)
{
    m_ignoreWhiteSpaces = ignore_;
}

template<typename _CmpCharT>
bool SimpleSearch<_CmpCharT>::getIgnoreWhiteSpaces() const
{
    return m_ignoreWhiteSpaces;
}

template<typename _CmpCharT>
void SimpleSearch<_CmpCharT>::search()
{
    kmpSearch();
}

template<typename _CmpCharT>
void SimpleSearch<_CmpCharT>::replace()
{
    int sizeDifferent = m_replacement.length() - m_needle.length();
    int offset = 0;     // Смещение при замене needle на replacement.

    for (int index : m_fIndexes)
    {
        index += offset;
        m_data.remove(index, m_needle.length());
        m_data.insert(index, m_replacement);
        offset += sizeDifferent;
    }
}

template<typename _CmpCharT>
QVector<int> * SimpleSearch<_CmpCharT>::prefixFunction()
{
    QVector<int> *pFunction =
            new QVector<int>;
    pFunction->resize(m_needle.length());
    pFunction[0] = 0;

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
            pFunction[current] = !_CmpCharT::eq(m_needle[current],
                                                m_needle[0]) ? 1 : 0;
        }
        else
        {
            pFunction[current] = candidate + 1;
        }
    }

    return pFunction;
}

template<typename _CmpCharT>
void SimpleSearch<_CmpCharT>::kmpSearch()
{
    // Получение префикс-функции и вспомогательных переменных.
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
                m_fIndexes->push_back(abs(current - matchedP));
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
