#ifndef CI_CMPCHAR_H
#define CI_CMPCHAR_H

/*
 * Case insensetive compare char.
 * 's' == 's'
 * 'S' == 's'
 **/

#include <QChar>

struct ci_cmpchar
{
    static inline bool eq(const QChar c1, const QChar c2) noexcept
    {
        return c1.toUpper() == c2.toUpper();
//        return std::toupper(static_cast<unsigned char>(c1)) ==
//                std::toupper(static_cast<unsigned char>(c2));
    }

    static inline bool lt(const QChar c1, const QChar c2) noexcept
    {
        return c1.toUpper() < c2.toUpper();
//        return std::toupper(static_cast<unsigned char>(c1)) <
//                std::toupper(static_cast<unsigned char>(c2));
    }
};

#endif // CI_CMPCHAR_H
