#ifndef S_CMPCHAR_H
#define S_CMPCHAR_H

/*
 * Case sensetive compare char.
 * 's' == 's'
 * 'S' != 's'
 **/

struct cs_cmpchar
{
    static inline bool eq(char c1, char c2) noexcept
    {
        return c1 == c2;
    }

    static inline bool lt(char c1, char c2) noexcept
    {
        return c1 < c2;
    }
};

#endif // S_CMPCHAR_H
