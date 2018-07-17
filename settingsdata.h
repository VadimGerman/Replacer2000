#ifndef SETTINGSDATA_H
#define SETTINGSDATA_H

#include <QString>

enum class FileFilterMaskType { IgnoreLikeThis,
                                UseOnlyLikeThis };

struct BaseSettings
{
    // Directories an files.
    bool searchInSubDirectories;
    bool caseSensetiveForFiles;
    bool searchInArchives;


    FileFilterMaskType maskType;
    QString fileMask;
    QString commentType;
};

struct AllSettings : public BaseSettings
{
    // Search.
    bool caseSensetive;
    bool ignoreWhiteSpaces;
    bool doesntContain;
    bool wholeWordsOnly;
    bool useRegExp;
    bool ignoreCommented;
};

#endif // SETTINGSDATA_H
