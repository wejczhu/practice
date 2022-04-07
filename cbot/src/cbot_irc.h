#ifndef CBOT_IRC_H
#define CBOT_IRC_H

#include <sc-collection.h>
#include <stdbool.h>

#include "cbot/cbot.h"
#include "libric_rfcnumeric.h"
#include "libircclient.h"

struct names_rq
{
    struct sb_list_head list;
    char *channel;
    struct sc_charbuf names;
}




#endif