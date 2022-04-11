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

struct cbot_irc_backend
{
    irc_sesssion_t *session;
    irc_callbacks_t callbacks;
    struct cbot *bot;
    bool connected;
    struct sc_list_head join_rqs;
    struct sc_list_head topic_rqs;
    struct sc_list_head names_rqs;
    char *host;
    int port;
    char *password;
};

#endif