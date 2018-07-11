#include "regexpsearch.h"

RegExpSearch::RegExpSearch(SearchData *inData_, QString &data) :
    m_needle(inData_->needle.toString()),
    m_replacement(inData_->replacement),
    m_data(data)
{
    m_foundIndexes= new QQueue<QPair<int, QString> >;
}

RegExpSearch::~RegExpSearch()
{

}

QQueue<QPair<int, QString> > *RegExpSearch::search()
{
    int pos = 0;

    while((pos = m_needle.indexIn(m_data, pos)) != -1)
    {
        QString foundString = m_data.mid(pos, m_needle.matchedLength());
        m_foundIndexes->push_back(qMakePair(pos, foundString));
        pos += m_needle.matchedLength();
    }

    return m_foundIndexes;
}

QString &RegExpSearch::replace()
{
    int offset = 0; // Смещение.
    QString replacement = m_replacement.toString();

    for (auto res : *m_foundIndexes)
    {
        int index = res.first + offset;
        m_data.remove(index, res.second.length());
        m_data.insert(index, replacement);
        offset += replacement.length() - res.second.length();
    }
}
