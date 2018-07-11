#ifndef SEARCH_H
#define SEARCH_H

#include "simplesearch.h"
#include "regexpsearch.h"
#include "simplereplace.h"
#include "ci_cmpchar.h"
#include "cs_cmpchar.h"

typedef SimpleSearch<cs_cmpchar> CS_Search;
typedef SimpleSearch<ci_cmpchar> CI_Search;
class RegExpSearch;
class SimpleReplace;

#endif // SEARCH_H
