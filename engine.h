#ifndef ENGINE_H
#define ENGINE_H

/*
 * Класс который владеет всеми объектами и выполняет
 * основную логику сязанную с решениями как искать и где искать.
 * Если вызывается деструктор класса, то только в конце программы
 * или по вызову глобального clean, в результате чего все настройки
 * и данные сбросятся к изначальному состоянию.
 **/

#include <QFile>

#include "search.h"

class Engine
{
    QString m_needle;
    QString m_replacement;
    QList<QString> *m_files;
    SimpleResultData *m_simpleResult;
//    RXResultData *m_rXResult;

    void simpleSearch() const;

public:
    // Настройки поиска.
    bool m_caseSensetive;
    bool m_ignoreWhiteSpaces;
    bool m_doesntContain;
    bool m_wholeWordsOnly;
    bool m_useRegExp;

    Engine();
    ~Engine();

    void setNeedle(const QString &needle_);
    void setReplacement(const QString &replacement_);

    void setFilesList(QList<QString> *files_);

    void search();
    void replace();
    // QAbstractItemModel * getResult();
    // QString getStatistic();
};

#endif // ENGINE_H
