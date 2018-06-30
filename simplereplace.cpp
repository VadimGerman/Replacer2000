#include "simplereplace.h"

void SimpleReplace::replace(ReplaceData &vars, QString &dataStr)
{
    int sizeDifferent =
            vars.replacement.length() -
            vars.needle.length();
    int offset = 0;     // Смещение при замене needle на replacement.

    for (auto index : *vars.indexes)         /// TODO: Может лучше int &index?
    {                                        /// Будем иметь актуальные индексы.
        index += offset;
        dataStr.remove(index, vars.needle.length());
        dataStr.insert(index, vars.replacement.toString());
        offset += sizeDifferent;
    }
}
