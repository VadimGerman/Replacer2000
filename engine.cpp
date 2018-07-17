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
    m_simpleResult = new QMap<QString, QQueue<int> *>;
    m_regExpResult = new QMap<QString, QQueue<QPair<int, QString> >*>;
}

Engine::~Engine()
{

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
    if (m_useRegExp)
    {
        regExpReplace();
    }
    else
    {
        simpleReplace();
    }
}

void Engine::clear()
{

    m_needle = "";
    m_replacement = "";
    m_files->clear();

    for (auto &res : *m_simpleResult)
        delete res;
    m_simpleResult->clear();
    for (auto &res: *m_regExpResult)
        delete res;
    m_regExpResult->clear();

    m_caseSensetive = true;
    m_ignoreWhiteSpaces = false;
    m_doesntContain = false;
    m_wholeWordsOnly = false;
    m_useRegExp = false;
    m_ignoreCommented = false;
}

QMap<QString, QQueue<int> *> *Engine::getSimpleResult()
{
    return m_simpleResult;
}

QMap<QString, QQueue<QPair<int, QString> > *> *Engine::getRegExpResult()
{
    return m_regExpResult;
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
                continue;

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
    // m_regExpResult = ...;


    SearchData *searchData = new SearchData { m_needle,
                                              m_replacement };

    for (auto &path : *m_files)
    {
        try
        {
            QString fileData;               /// TODO: вынести открытие и закрытие файла в отдельные методы.
            QFile *file = new QFile(path);
            if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
                continue;

            // Чтение файла.
            fileData = file->readAll();
            file->close();

            RegExpSearch *search = new RegExpSearch(searchData,
                                                    fileData,
                                                    m_caseSensetive);
            m_regExpResult->insert(path, search->search());
        }
        catch (...)
        {
            // Error message.
        }
    }

    delete searchData;
}

void Engine::simpleReplace()
{
    SimpleReplaceData rData;
    rData.needle = m_needle;
    rData.replacement = m_replacement;
    QFile *file = new QFile();

    // Replace for all files in result variable.
    for (auto it = m_simpleResult->begin();
         it != m_simpleResult->end();
         ++it)
    {
        rData.indexes = *it;
        // Read data from file and close it.
        file->setFileName(it.key());                                /// TODO: Need try/catch
        if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            continue;
        QString data = file->readAll();
        file->close();

        // Make the replace and rewrite file.
        SimpleReplace::replace(rData, data);
        if (!file->open(QIODevice::ReadWrite | QIODevice::Truncate))
            continue;
        file->seek(0);
        file->write(data.toStdString().c_str(), data.length());
        file->close();
    }
}

void Engine::regExpReplace()
{
    RegExpReplaceData rData;
    rData.needle = m_needle;
    rData.replacement = m_replacement;
    QFile *file = new QFile();

    // Replace for all files in result variable.
    for (auto it = m_regExpResult->begin();
         it != m_regExpResult->end();
         ++it)
    {
        rData.indexes = *it;
        // Read data from file and close it.
        file->setFileName(it.key());                                /// TODO: Need try/catch
        if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
            continue;
        QString data = file->readAll();
        file->close();

        // Make the replace and rewrite file.
        RegExpReplace::replace(rData, data);
        if (!file->open(QIODevice::ReadWrite | QIODevice::Truncate))
            continue;
        file->seek(0);
        file->write(data.toStdString().c_str(), data.length());
        file->close();
    }
}
