#ifndef S_CMPCHAR_H
#define S_CMPCHAR_H

/*
 * Case sensetive compare char.
 * 's' == 's'
 * 'S' != 's'
 **/

#include <QChar>

struct cs_cmpchar
{
    static inline bool eq(QChar c1, QChar c2) noexcept
    {
        return c1 == c2;
    }

    static inline bool lt(QChar c1, QChar c2) noexcept
    {
        return c1 < c2;
    }
};

#endif // S_CMPCHAR_H
