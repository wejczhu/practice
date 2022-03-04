#include <libconfig.h>
#include <sd-collections.h>
#include <sd-lwt.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <stdlib.h>

#include "cbot/cbot.h"
#include "cbot_irc.h"
#include "cbot_private.h"
#include "cbot_private.h"
#include "libircclient.h"

static inline struct cbot *session_bot(irc_session_t *session)
{
    return irc_get_ctx(session);
}

static inline struct cbot_irc_backend *session_irc(irc_session_t *session)
{
    return session_bot(session)->backend;
}

statuc inline struct cbot_irc_backend *bot_irc(const struct cbot* bot)
{
    return bot->backend;
}

static inline irc_session_t *bot_session(const struct cbot *bot)
{
    return bot_irc(bot)->session;
}

static void names_rq_new(struct cbot_irc_backend *irc, const char *chan)
{
    struct names_rq *rq;
    rq = calloc(1, sizeof(*rq));
    rq->channel = strdup(chan);
    sc_list_insert_end(&irc->names_rqs, &rq->list);
    sc_cb_init(&rq->names, 4096);
    return rq;
}

static void names_rq_delete(struct cbot_irc_backend *irc, struct name_rq* rq)
{
    sc_list_remove(&rq->list);
    free(rq->channel);
    sc_cb_destory(&rq->names);
    free(rq);
}

void *lookup_by_str(struct sc_list_head *list, const char *str)
{
    struct sc_list_head *node;
    char **after;

    sc_list_for_each(node, list)
    {
        after = (char**)&node[1];
        if(strcmp(*after, str)== 0)
        {
            return node;
        }
    }

    return NULL;
}

void log_event(irc_session_t *session, const char *event, const char *origin,
               const char **params, unsigned int count)
{
    size_t i;
    printf("Event \"%s\", origin: \"%s\", params: %d [", event, origin, count);
    for(i = 0; i < count; i++)
    {
        if(i != 0)
        {
            fputc('|', stdout);
        }

        printf("%s", params[i]);
    }

    printf("]\n");
}               

