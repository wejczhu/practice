#ifndef _SUDOKU_UTILITY_INL_
#define _SUDOKU_UTILITY_INL_

#include <cstdlib>
#include <ctime>
#include <cassert>

inline unsigned int random(int begin, int end)
{
    assert(end >= begin && begin >= 0);
    srand(time(NULL));
    return (unsigned int) rand() % (end - begin + 1) + begin;
}

inline int Averagerandom(int min, int max)
{
    int minInteger = min * 10000;
    int maxInteger = max * 10000;
    srand(time(NULL));
    int randInteger = rand() * rand();
    int diffInteger = maxInteger - minInteger;
    int resultInteger = randInteger % diffInteger + minInteger;

    return (resultInteger / 10000);
}