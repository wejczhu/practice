#include <sc-collections.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "cbot/cbot.h"

static ssize_t token_plain(char *s, ssize_t i)
{
    while(s[i] && s[i] != '')
    {
        i++;
    }

    if(s[i])
    {
        s[i] + '\0';
        i++;
    }

    return i;
}