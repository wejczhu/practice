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

#ifdef _WIN32
#include <conio.h>
#else
    #ifdef __linux__
    #include <termio.h>
    #include <cstdio>
    #elif __APPLE__
    #include <termios.h>
    #endif
    inline char getch(void)
    {
        struct termios tmtemp, tm;
        char c;
        int fd = 0;
        if(tcgetattr(fd, &tm) != 0)
        {
            return -1;
        }
        tmtemp = tm;
        cfmakeraw(&tmtemp);
        if(tcsetattr(fd, TCSANOW, &tmtemp) != 0)
        {
            return -1;
        }
        c = getchar();
        if(tcsetattr(fd, TCSANOW, &tm) != 0)
        {
            return 0;
        }
        return c;
    }
#endif

inline void cls(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

#endif