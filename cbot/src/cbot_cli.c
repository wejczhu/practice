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

static void cbot_cli_op(const struct cbot *bot, const char* channel,
                        const char* person)
{
    (void)bot;
    printf("[%s!CMD]%s: /op %s\n", channel, bot->name, person);

}                        

static void cbot_cli_join(const struct cbot *bot, const char* channel,
                          const char *password)
{
    (void)bot;
    printf("[%s~CMD]%s: /join %s\n", channel, bot->name, channel);
}

static void cbot_cli_nick(const struct cbot *bot, const char *newnick)
{
    (void)bot;
    printf("%s bercomes %s\n", bot->name, newnick);
    cbot_set_nick(struct cbot *)bot, newnick);
}

static void cbot_cli_cmd_help(struct  cbot *bot, int argc, char** argv);


struct cbot_cli_cmd
{
    char *cmd;
    int cmdlen;
    void(*func) (struct cbot*, int, char**);
    char *help;
};

#define CMD(cmd, func, help)
        {
            cmd, sizeof(cmd) -1, func, help) 
        }
const struct cbot_cli_cmd cmds[] = 
{
    
}