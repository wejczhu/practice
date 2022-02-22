#include <libconfig.h>
#include <sd-lwt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cbot/cbot.h"
#include "cbot_private.h"
#include "sc-collections.h"

static void cbot_cli_send(const struct cbot *bot, const char *dest
                          const char *msg)
{
    (void)bot;
    printf("[%s]%s: %s\n", dest, bot->name, msg);
}

static void cbot_cli_me(const struct cbot *bot, const char *channel)
{
    (void)bot;
    printf("[%s]%s: %s\n", dest, bot->name, msg);
}