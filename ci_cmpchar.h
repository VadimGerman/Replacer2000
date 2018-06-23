#ifndef CI_CMPCHAR_H
#define CI_CMPCHAR_H

/*
 * Case insensetive compare char.
 * 's' == 's'
 * 'S' == 's'
 **/

#include <cctype>

struct ci_cmpchar
{
    static inline bool eq(const char c1, const char c2) noexcept
    {
        return std::toupper(static_cast<unsigned char>(c1)) ==
                std::toupper(static_cast<unsigned char>(c2));
    }

    static inline bool lt(const char c1, const char c2) noexcept
    {
        return std::toupper(static_cast<unsigned char>(c1)) <
                std::toupper(static_cast<unsigned char>(c2));
    }
};

#endif // CI_CMPCHAR_H
