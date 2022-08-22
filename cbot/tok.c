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

static ssize_t token_quote(char *s, ssize_t i)
{
    size_t shift = 0;
    while(s[i])
    {
        s[i - shift] = s[i];
        if(s[i] == '"')
        {
            if(s[ i + 1] == ' ' || s[i + 1] == '\0')
            {
                i++;
                shift++;
            }
            else if(s[i + 1] )
        }
    }
}