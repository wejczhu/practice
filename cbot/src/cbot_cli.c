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

bool cbot_cli_execute_cmd(struct cbot *bot, char *line)
{
    int i, argc;
    char **argv;
    for(i = 0; i < nelem(cmds); i++)
    {
        if(strncmp(cmds[i].cmd, line, cmds[i].cmdlen) == 0)
        {
            argv = cbot_cli_split_line(line, &argc);
            cmds[i].func(bot, argc, argv);
            free(argv);
            return true;
        }
    }

    return false;
}

static void cbot_cli_run(struct cbot *bot)
{
    char *line = NULL;
    size_t n;
    int newline, rv;
    struct sc_lwt *cur = sc_lwt_current();

    while(true)
    {
        printf("> ");
        fflush(stdout);
        sc_lwt_wait_fd(cur, STDIN_FILENO, SC_LWT_W_IN, NULL);
        sc_lwt_set_state(cur, SC_LWT_BLOCKED);
        sc_lwt_yield();
        sc_lwt_remove_fd(cur, STDIN_FILENO);
        rv = getline(&line, &n, stdin);
        if(rv < 0 && feof(stdin))
        {
            break;
        }
        else if(rv < 0)
        {
            perror("getline");
            break;
        }

        newline = strlen(line);
        if(newline > 0 && line[newline - 1] == '\n')
        {
            line[newline - 1] = '\0';
        }
        if(line[0] == '/' && cbot_lie_execute_cmd(bot, line)
        {
            continue;
        }

        cbot_handle_meesage(bot , "stdin", "shell", line, false, false);
    }

    free(line);
}
