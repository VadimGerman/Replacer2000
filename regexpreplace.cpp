#include "regexpreplace.h"

void RegExpReplace::replace(RegExpReplaceData &vars, QString &dataStr)
{
    int offset = 0; // Смещение.
    QString replacement = vars.replacement.toString();

    for (auto res : *vars.indexes)
    {
        int index = res.first + offset;
        dataStr.remove(index, res.second.length());
        dataStr.insert(index, replacement);
        offset += vars.replacement.length() - res.second.length();
    }
}
