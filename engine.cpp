#include "engine.h"

Engine::Engine()
{
    m_needle = "";
    m_replacement = "";
    m_files = nullptr;
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

void Engine::setFilesList(QList<QString> *files_)
{
    m_files = files_;
}

void Engine::search()
{
    // Подготовка списка файлов.

    // Настройка поиска в соответствии с параметрами.
    if (m_useRegExp)
    {
        if (m_wholeWordsOnly)
            m_needle = "\\b(" + m_needle + ")\\b";
        if (m_doesntContain)
        {}
        if (m_ignoreWhiteSpaces)
        {}
        // m_rXResult = ...;
    }
    else
    {
        simpleSeatch();
    }
}

void Engine::replace()
{

}

void Engine::simpleSearch() const
{
    while (auto &filePath : *m_files)
    {
        try
        {
            QString fileData;
            QFile *file = new QFile(filePath);
            if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            {
                continue;
            }

            // Чтение файла.
            fileData = file->readAll();
            file->close();

            SimpleSearch *search = new SimpleSearch()
            m_simpleResult =
        }
        catch (...)
        {
            continue;
        }
    }
}
