#include "engine.h"

Engine::Engine()
{
    m_needle = "";
    m_replacement = "";
    m_files = new QQueue<QString>;
    m_caseSensetive = true;
    m_ignoreWhiteSpaces = false;
    m_doesntContain = false;
    m_wholeWordsOnly = false;
    m_useRegExp = false;
    m_simpleResult = new QMap<QString, QQueue<int>*>;
}

void Engine::setNeedle(const QString &needle_)
{
    m_needle = needle_;
}

void Engine::setReplacement(const QString &replacement_)
{
    m_replacement = replacement_;
}

void Engine::addFile(const QString &file)
{
    m_files->push_back(file);
}

void Engine::search()
{
    // Настройка поиска в соответствии с параметрами.
    if (m_useRegExp)
    {
        regExSearch();
    }
    else
    {
        simpleSearch();
    }
}

void Engine::replace()
{

}

QMap<QString, QQueue<int> *> *Engine::getSimpleResult()
{
    return m_simpleResult;
}

void Engine::simpleSearch()
{
    SearchData *searchData = new SearchData { m_needle,
                                              m_replacement };

    for (auto &path : *m_files)
    {
        try
        {
            QString fileData;               /// TODO: вынести открытие и закрытие файла в отдельные методы.
            QFile *file = new QFile(path);
            if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            {
                continue;
            }

            // Чтение файла.
            fileData = file->readAll();
            file->close();

            if (m_caseSensetive)    /// TODO: Вообще как-то по ебанутому, при каждой итерации проверять что ли?
            {
               CS_Search *search = new CS_Search(searchData,
                                                 fileData,
                                                 m_ignoreWhiteSpaces);
               m_simpleResult->insert(path, search->search());
            }
            else
            {
                CI_Search *search = new CI_Search(searchData,
                                                  fileData,
                                                  m_ignoreWhiteSpaces);
                m_simpleResult->insert(path, search->search());
            }
        }
        catch (...)
        {
            // Error message.
        }
    }

    delete searchData;
}

void Engine::regExSearch()
{
    QString needle = m_needle;
    if (m_wholeWordsOnly)
        needle = "\\b(" + needle + ")\\b";
    if (m_doesntContain)
    {}
    if (m_ignoreWhiteSpaces)
    {}
    // m_rXResult = ...;
}
