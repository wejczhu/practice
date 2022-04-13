#ifndef CBOT_PRIVATE_H
#define CBOT_PRIVATE_H

#include <inttypes.h>
#include <stdarg.h>

#include <curl/curl.h>
#include <libconfig.h>
#include <sc-collections.h>
#include <sc-lwt.h>
#include <sc-regex.h>
#include <sqlite3.h>

#include "cbot/cbot.h"

struct cbot_plugpriv;

struct cbot_handler
{
    cbot_handler_t handler;

    void *user;

    struct cbot_plugpriv *plugin;

    struct sc_regex *regex;

    struct sc_list_head handler_list;

    struct sc_list_head plugin_list;
};

struct cbot_plugpriv
{
    cbot_handler_t handler;
    void *user;
    struct cbot_plugpriv *plugin;

    struct sc_regex *regex;

    struct sc_list_head handler_list;

    struct sc_list_head plugin_list;
}



#endif // CBOT_PRIVATE_H
