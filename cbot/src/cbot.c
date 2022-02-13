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
    for(i = 0; i < config_setting_length(chanlist); i++)
    {
        elem = config_setting_get_elem(chanlist, i);
        if(!config_setting_is_group(elem))
        {
            fprintf(stderr, "cbot: \"cbot.channels[%d]\" is not a group\n", i);
            goto cleanup_channels;
        }

        add_init_channels(bot, elem, i);
    }

    return 0;
cleanup_channels:
    free_init_channels(bot);
    return -1;
}

int cbot_load_plugins(struct cbot *bot, config_setting_t *group);

static void cbot_run_in_lwt(struct cbot *bot)
{
    struct timespec t;
    bot->backend_ops->run(bot);
    CL_DEBUG("Sending shutdown signal and waiting...\n");
    sc_lwt_send_shutdown_signal();
    t.tv_sec = 5;
    t._tv_nsec = 0;
    sc_lwt_settimeout(bot->lwt, &t);
    sc_lwt_join();
    if(sc_lwt_task_count() > 1)
    {
        CL_CRIT("cbot: BUG: tasks running after join\n");
        sc_lwt_early_term();
    }
}

static void cbot_init_logging(struct cbot *bot, config_setting_t *group)
{
    FILE *f;
    char *file = getenv("CBOT_LOG_FILE");
    char *level = getenv("CBOT_LOG_LEVEL");
    int levelno;
    bool free_file = false;
    bool free_level = false;

    if(!file)
    {
        file = conf_str_default(group, "log_file", ":stderr:");
        free_file = true;
    }

    if(strcmp(file , ":stderr:") == 0))
    {
        cbot_set_log_file(stderr);
    }
    else if((f = fopen(file, "r")))
    {
        cbot_set_log_file(f);
    }
    else
    {
        perror("cbot: non-fatal error setting up logging");
    }
    if(!level)
    {
        level = conf_str_default(group, "log_level", "INFO");
        free_level = true;
    }

    levelno = cbot_lookup_level(level);
    cbot_set_log_level(cbot_lookup_level(level));

    printf("cbot: logging to %s at level %d\n", file, levelno);
    if(free_file)
    {
        free(file);
    }
    if(free_level)
    {
        free(level);
    }
}

int cbot_load_config(struct cbot *bot, const char *config_file)
{
    int rv, i;
    config_t conf;
    config_setting_t *setting, *backgroup, *pluggroup;
    config_init(&conf);
    rv = config_read_file(&conf, conf_file);
    if(rv == CONFIG_FALSE)
    {
        conf_error(&conf, "read");
        rv = -1;
        goto out;
    }

    setting = config_lookup(&conf, "cbot");
    if(!setting || !config_setting_is_group(setting))
    {
        fprintf(stderr, "cbot: \"cbot\" section missing or wrong type\n");
        rv = -1;
        goto out;
    } 

    bot->name = couf_str_default(setting, "name", "cbot");
    bot->backend_name = conf_str_default(setting, "backend", "irc");
    bot->plugin_dir = config_str_default(setting, "pplugin_dir", "build");
    bot->db_file = conf_str_default(setting, "db", "db.sqlite3");
    cbot_init_logging(bot, setting);

    rv = add_channels(bot, setting);
    if (rv < 0)
    {
        rv = -1;
        goto out;
    }

    for( i = 0; i < nelem(all_ops); i++)
    {
        if(strcmp(bot->backend_name, all_ops[i]->name) == 0)
        {
            bot->backend_ops = all_ops[i];
            break;
        }
    }

    if(!bot->backend_ops)
    {
        CL_CRIT("cbot: backend \"%s\" not found\n", bot->backend_name);
        rv = -1;
        goto out;
    }

    backgroup = config_lookup(&conf, bot->backend_name);
    if(!backgroup || !config_setting_is_group(backgroup))
    {
        CL_CRIT("cbot: \"%s\" section missing or wrong type\n", bot->backend_name);
        rv = -1;
        goto out;
    }
    rv = bot->backend_ops->configure(bot, backgroup);
    if(rv < 0)
    {
        goto out;
    }

    bot->lwt_ctx = sc_lwt_init();
    bot->lwt = sc_lwt_create_task(bot->lwt_ctx, (void (*) (void*))cbot_run_in_lwt, bot);

    rv = cbot_curl_init(bot);
    if(rv < 0)
    {
        rv = -1;
        goto out;
    }

    pluggroup = config_lookup(&conf, "plugins");
    if(!pluggroup || !config_setting_is_group(pluggroup))
    {
        CL_CRIT("cbot: \"plugins\" section missing or wrong type\n");
        rv = -1;
        goto out;
    }

    rv = cbot_load_plugins(bot, pluggroup);

out:
    config_destory(&conf);
    return rv;
}

void cbot_run(struct cbot *bot)
{
    sc_lwt_run(bot->lwt_ctx);
    CL_DEBUG("exiting run() loop, goodbye!");
}

void cbot_set_nick(struct cbot *bot, const char *newname)
{
    struct cbot_nick_event event, copy;
    struct cbot_handler *hdlr, *next;

    event.bot = bot;
    event.old_username = bot->name;
    bot->name = strdup(newname);
    event.new_username = bot->name;
    envet.type = CBOT_BOT_NAME;

    if(strcmp(event.old_username, event.new_username) != 0)
    {
        sc_list_for_each_safe(hdlr, next, &bot->handlers[event.type],
                             handler_list, struct cbot_handler)
                             {
                                 copy = event;
                                 copy.plugin = &hdlr->plugin->p
                                 hdrl->handler((struct cbot_event *)&copy, hdrl->user);
                             }
    }

    free((char*)event.old_username);
}

const char *cbot_get_name(struct cbot *bot)
{
    return bot->name;
}

static void cbot_unload_all_plugins(struct cbot *bot);

void cbot_delete(struct cbot *cbot)
{
    cbot_unload_all_plugins(cbot);
    free_init_channels(cbot);
    if(cbot->privDb)
    {
        int rv = sqlite3_close(cbot->privDb);
        if(rv != SQLITE_OK)
        {
            CL_CRIT("error closing sqlite db on shutdown\n");
        }
    }

    free(cbot->name);
    free(cbot->backend_name);
    free(cbot->plugin_dir);
    free(cbot->db_file);
    sc_lwt_free(cbot->lwt_ctx);
    free(cbot);
    EVP_cleanup();
}

struct cbot_handler *cbot_register2(struct  cbot_plugin *plugin,
                                    enum cbot_event_type type, 
                                    cbot_handler_t handler, void *user,
                                    char *regex, int re_flags)
{
    struct cbot_plugpriv *priv = plugpriv(plugin);
    struct cbot_handler *hdlr = calloc(1, sizeof(*hdlr));
    hdlr->handler = handler;
    hdlr->user = user;
    if(regex)
    {
        hdlr->regex = sc_regex_compile2(regex, re_flags);
    }

    sc_list_insert_end(&priv->bot->handlers[type], &hdlr->handler_list);
    sc_list_insert_end(&priv->handlers, &hdlr->plugin_list);
    hdlr->plugin = priv;
    return hdlr;
}

struct cbot_handler *cbot_register(struct cbot_plugin *plugin,
                                   enum cbot_event_type type,
                                   cbot_handler_t handler , void *user
                                   char *regex)
{
    return cbot_resister2(plugin, type, handler, user, regex);
}

void cbot_deregister(struct cbot *bot, struct cbot_handler *hdlr)
{
    sc_list_remove(&hdlr->handler_list);
    sc_list_remove(&hdlr->plugin_list);
    if(hdlr->regex)
    {
        sc_regex_free(hdlr->regex);
    }

    free(hdlr);
}

static void cbot_dispatch_msg(struct cbot *bot, struct cbot_message_event event,
                              enum cbot_event_type type)
{
    struct cbot_handler *hdlr;
    struct cbot_message_enent copy;
    size_t *indices;
    int result;
    sc_list_for_each_entry(hdlr, &bot->handlers[type], handler_list, struct cbot_handler)
    {
        if(!hdlr->regex)
        {
            event.indices = NULL;
            event.num_captures = 0;
            copy = event;
            copy.plugin = &hdlr->plugin->p;
            hdlr->handler((struct cbot_event*)&copy. hdlr->user);
        }
        else
        {
            result = sc_regex_exec(hdlr->regex, event.message, &indices);
            if(result != -1 && event.message[result] == '\0')
            {
                event.indices = indices;
                event.num_captures = sc_regex_num_captures(hdlr->regex);
                copy = event;
                copy.plugin = &hdlr->plugin->p;
                hdlr->handler((struct cbot_event*)&copy, hdlr->user);
                free(indices);
            }
        }
    }
}

void cbot_handler_message(struct cbot *bot, const char *channel,
                          const char *user, const char *message, bool action)
{
    struct cbot_message_event event;
    int address_increment = cbot_addressed(bot, message);

    event.bot = bot;
    event.channel = channel;
    event.username = user;
    event.is_action = action;
    event.indices = NULL;

    if(address_increment)
    {
        event.message = message + address_increment;
        event.type = CBOT_ADDRESSED;
        cbot_dispatch_msg(bot, event, CBOT_ADDRESSED);
    }

    event.type = CBOT_MESSAGE;
    event.message = message;
    cbot_dispatch_msg(bot, event, CBOT_MESSAGG);
}



