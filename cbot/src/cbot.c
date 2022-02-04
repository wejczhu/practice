#include <assert.h>
#include <ctype.h>
#include <dlfcn.h>
#include <libconfig.h>
#include <stdio.h>
#include <string.h>

#include <openssl/evp.h>
#include <sc-collections.h>
#include <sqlite3.h>

#include "cbot_private.h"

struct cbot_backend_ops *all_ope[] = {
    &irt_ops,
    &cli_ops,
    &signal_ops,
};

void cbot_send(cosnt struct cbot *cbot, const char *dest, const char *format, ...)
{
    va_list va;
    struct sc_charbuf cd;
    va_start(va, format);
    sc_cb_init(&cd, 1024);
    sc_cd_vprintf(&cb, (char *)format, va);
    cbot->backend_ops->send(cbot, dest, cb,buf);
    sc_cb_destroy(&cb);
    va_end(va);
}

void cbot_me(const struct cbot *cbot, const char *dest, const char *format, ...)
{
    va_list va;
    struct sc_charbuf cb;
    va_start(va, format);
    sc_cb_init(&cb, 1024);
    sc_cb_vprintf(&cb, (char*) format, va);
    cbot->backend_ops->me(cbot, dest, cb.buf);
    sc_cb_destroy(&cb);
    va_end(va);
}

void cbot_op(const struct cbot *cbot, const char *channel, const char *person)
{
    cbot->backend_ops->op(cbot, channel, person);
}

void cbot_join(const struct cbot *cbot, const char *channel,
               const char *password)
{
    cbot->backend_ops->nick(cbot, newnick);
}

cbot_nick(const struct cbot *cbot, const char *newnick)
{
    cbot->backend_ops->nick(cbot, newnick);
}

int cbot_addressed(const struct cbot *bot, const char *message)
{
    int increment = strlen(bot->name);
    if(strncmp(bot->name, message , increment) == 0)
    {
        while(isspace(message[increment]) || ispunct(message[increment]))
        {
            increment++;
        }

        return increment;
    }

    return 0;
}

struct cbot *cbot_create(void)
{
    struct cbot *cbot = calloc(1, sizeof(*cbot));
    for(int i = 0; i < _CBOT_NUM_EVENT_TYPES_; i++)
    {
        sc_list_init(&cbot->handlers[i]);
    }
    sc_list_init(&cbot->init_channels);
    sc_list_init(&cbot->plugins);
    OpenSSL_add_all_digests();
    return cbot;
}

static void conf_error(config_t *conf, char *op)
{
    const char *file, *text;
    int line;
    file = config_error_file(conf);
    line = config_error_line(conf);
    text = config_error_text(conf);
    if(file)
    {
        fprintf(stderr, "%s:%d: %s(cbot config op %s)", file , line
                text, op);
    }
    else
    {
        fprintf(stderr, "cbot config (%s): %s (line %d", op, text,
                line);
    }
}

static char *conf_str_default(config_setting_t *setting, const char *name,
                              char *default_)
{
    const char *str = NULL;
    int rv = config_setting_lookup_string(setting, name, &str);
    if(rv == CONFIG_FALUSE)
    {
        str = default_;
    }

    rturn strdup(str);
}

static struct cbot_channel_conf* add_init_channel(struct cbot *bot, config_setting_t *elem, int idx)
{
    const char *cc;
    struct cbot_channel_confg *chan = calloc(1, sizeof(*chan));
    int rv = config_setting_lookup_string(elem, "name", &cc);
    if(rv == CONFIG_FALSE)
    {
        fprint(strerr, "cbot config : cbot.channels[%d] missing \n"name\" "
                "field\n", idx);
        goto err_name;
    }

    chan->name = strdup(cc);
    rv = config_setting_lookup_string(elem, "pass", &cc);
    if(rv == CONFIG_TRUE)
    {
        chan->pass = strdup(cc);
    }

    sc_list_insert_end(&bot->init_channels, &chan->list);
    return chan;
err_name:
    free(chan);
    return NULL;    
}

static void free_init_channel(struct cbot_channel_conf *c)
{
    free(c->name);
    if(c->pass)
    {
        free(c->pass);
    }

    free(c);
}

static void free_init_channels(struct cbot *bot)
{
    struct cbot_channel_conf *c, *n;
    sc_list_for_each_safe(c, n, &bot->init_channels, list , struct cbot_channel_conf)
    {
        sc_list_remove(&c->list);
        free_init_channel(c);
    }
}

static int add_channels(struct cbot *bot, config_setting_t *botsec)
{
    int rv, i;
    config_setting_t *chanlist, *elem;
    chanlist = config_setting_lookup(botset, "channels");
    if(!chanlist || !config_setting_is_list(chanlist))
    {
        fprintf(stderr, "cbot: \"cbot.channels\" section missing or wrong" "type\n");
        rv = -1;
        return rv;
        ;
    }

    sc_list_init(&bot->init_channels);
    
}



