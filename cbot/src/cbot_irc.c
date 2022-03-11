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

static void add_all_names(struct cbot *bot, struct names_rq *rq)
{
    char *nick = strtok(rq->name.buf, " ");
    do
    {
        if(nick[0] == '~' || nick[0] == '&' || nick[0] == '+' ||
           nick[0] == '%')
        {
            nick++;
        }

        cbot_add_membership(bot, nick, rq->channel);

    } while ((nick = strtok(NULL, " ")) != NULL);
}

static void event_rpl_namereply(irc_session_t *session, const char *origin
                                const char **params, unsigned int count)
{
    struct cbot_irc_backend *irc = session_irc(session);
    struct names_rq *rq = lookup_by_str(&irc->names_rqs, params[2]);
    if(!rq)
    {
        fprintf(stderr, "ERR: unsolicited RPL_NAMREPLY for %s\n", params[2]);
        return;
    }

    cbot_clear_channel_memberships(bot, rq->channel);
    add_all_names(bot, rq);
    names_rq_delete(irc, rq);
}      

void event_rpl_endofnames(irc_session_t *session, const char *origin,
                          const char **params, unsigned int count)
{
    struct cbot_irc_backend *irc = session_irc(session);
    struct cbot *bot = session_bot(session);
    struct names_rq *rq = lookup_by_str(*irc->names_rqs,params[1]);
    if(!rq)
    {
        fprintf(stderr, "ERR: unsolicited RPL_ENDOFNAMES for %s\n", params[1]);
        return;
    }

    cbot_clear_channel_memberships(bot, rq->channel);
    add_all_names(bot, rq);
    names_rq_delete(irc, rq);
}                          

void event_rpl_topic(irc_session_t *session, unsigned int event,
                     const char *origin, const char **params, unsigned int count)
{
    struct cbot *bot = session_bot(session);
    cbot_set_channel_topic(bot, (char*) params[1], (char*)params[2]);
}

void event_numeric(irc_session_t *session, unsigned int event,
                   const char *origin, const char **params, unsigned int count)
{
    char buf[24];
    sprintf(buf, "%d", event);
    switch(event)
    {
        case 332:
            event_rpl_topic(session, origin, params, count);
            break;

        case 353:
            event_rpl_namreply(session, origin, params, count);
            break;

        case 366:
            event_rpl_endofnames(session, origin, params, count);
            break;
    }
    log_event(session, buf, origin ,params, cout);
}

void event_connect(irc_session_t *session, const char *event, 
                   const char *origin, const char **params, unsigned int count)
{
    struct cbot *bot = session_bot(session);
    struct cbot_channel_conf *c;
    sc_list_for_each_entry(c, &bot->init_channel s, list,
                            struct cbot_channel_conf)
    {
        cbot_join(bot, c->name, c->pass);
        irc_cmd_join(session, c->name, c->pass);
    }                            

    log_event(session, event, origin, params, count);
}

static inline void maybe_schedule(const struct cbot *bot)
{
    if(sc_lwt_current() != bot->lwt)
    {
        sc_lwt_set_state(bot->lwt, SC_LWT_RUNNABLE);
    }
}

static void cbot_irc_send(const struct cbot *cbot, const char * to
                          const char *msg)
{
    irc_session_t *session = bot_session(cbot);
    irc_cmd_msg(session, to, msg);
    maybe_schedule(cbot);
}                        

static void cbot_irc_me(const struct cbot *cbot, const char *to
                        const char *msg)
{
    irc_session_t *session = bot_session(cbot);
    irc_cmd_me (session, to, msg);
    maybe_schedule(cbot);
}
