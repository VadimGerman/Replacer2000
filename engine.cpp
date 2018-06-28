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
}

void Engine::setNeedle(const QString &needle_)
{
    m_needle = needle_;
}

void Engine::setReplacement(const QString &replacement_)
{
    m_replacement = replacement_;
}

void Engine::setFilesList(QQueue<QString> *files_)
{
    m_files = files_;
}

void Engine::search()
{
    // Подготовка списка файлов.

    // Настройка поиска в соответствии с параметрами.
    if (m_useRegExp)                /// TODO: Need factore?
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

void Engine::simpleSearch()
{
    SearchData *searchData = new SearchData { m_needle,
                                              m_replacement };

    for (auto &path : *m_files)
    {
        try
        {
            QString fileData;
            QFile *file = new QFile(path);
            if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            {
                continue;
            }

            // Чтение файла.
            fileData = file->readAll();
            file->close();

            if (m_caseSensetive)
            {
               CS_Search *search = new CS_Search(searchData,
                                                 fileData,
                                                 m_ignoreWhiteSpaces);
               search->search();
               search->replace();
               qDebug() << search->replace();
//               m_simpleResult =
            }
            else
            {
                CI_Search *search = new CI_Search(searchData,
                                                  fileData,
                                                  m_ignoreWhiteSpaces);
                search->search();
                search->replace();
                qDebug() << search->replace();
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
