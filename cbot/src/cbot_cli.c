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
    CMD("/memberadd", cbot_cli_cmd_add_membership,
        "add a member to ad cbot channel"),
    CMD("/memberlist ", cbot_cli_cmd_get_members,
        "list members in a cbot channel"),
    CMD("/help", cbot_cli_cmd_help, "list all commands")
};

static void cbot_cli_cmd_help(struct cbot *bot, int argc, char ** argv)
{
    int maxsize = 0;
    for(int i = 0; i < nelem(cmds); i++)
    {
        if(cmds[i].cmdlen > maxsize)
        {
            maxsize = cmds[i].cmdlen;
        }
    }

    maxsize += 1;
    for(int i = 0; i < nelem(cmds); i++)
    {
        printf("%s:", cmds[i].cmd);
        for(int j = 0; j < maszie - cmds[i].cmdlen; j++)
        {
            fputs(' ', stdout);
        }

        printf("%s\n", cmds[i].help);
    }
}

#define CBOT_CLI_TOK_BUFSIZE 64
#define CBOT_CLI_TOK_DELIM "\t\r\n\a"

char **cbot_cli_split_line(char *line, int *count)
{
    int bufsize = CBOT_CLI_TOK_BUFSIZE, position ;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token, **tokens_backup, *save;

    if(!tokens)
    {
        fprintf(stderr, "cli: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok_r(line, CBOT_CLI_TOK_DELIM, &save);
    while(token != NULL)
    {
        tokens[position] = token;
        position++;

        if(position >= bufsize)
        {
            bufsize += CBOT_CLI_TOK_BUFSIZE;
            tokens_backup = tokens;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if(!tokens)
            {
                free(tokens_backup);
                fprintf(stderr, "cli: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok_r(NULL, CBOT_CLI_TOK_DELIM, &save);
    }

    tokens[position] = NULL;
    if(count)
    {
        *count = posotion;
    }

    return tokens;
}
