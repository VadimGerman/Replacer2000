#ifndef ENGINE_H
#define ENGINE_H

/*
 * Класс который владеет всеми объектами и выполняет
 * основную логику сязанную с решениями как искать и где искать.
 * Если вызывается деструктор класса, то только в конце программы
 * или по вызову глобального clean, в результате чего все настройки
 * и данные сбросятся к изначальному состоянию.
 **/

#include "search.h"

class Engine
{
    QString m_needle;
    QString m_replacement;

public:
    Engine() = delete;
    Engine(QList<QString> *files);
    ~Engine();

    void setNeedle(const QString &needle_);
    void setReplacement(const QString &replacement_);

    void prepare();
    void search();
    void replace();
    // QAbstractItemModel * getResult();
    // QString getStatistic();
};

#endif // ENGINE_H
