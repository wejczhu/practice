#include <sqlite3.h>
#include <stdlib.h>

#include "cbot/cbot.h"
#include "cbot/db.h"
#include "cbot_private.h"
#include "sc-collections.h"

#define CBOTDB_UPSERT_FUNC(name, getter, inserter)
    int name(struct cbot *bot, char * ARG)
    {
        int RV = getter(bot, ARG);
        if(RV > 0)
        {
            return RV;
        }
        else
        {
            return inserter(bot, ARG);
        }
    }

static int cbot_db_get_user_id(struct cbot *bot, char *nick)
{
    CBOTDB_QUERY_FUNC_BEGIN(bot, void, "SELECT id FROM user WHERE")
    CBOTDB_BIND_ARG(text, nick);
    CBOTDB_SINGLE_INTEGER_RESULT();
}

static int cbot_db_insert_user(struct cbot* bot, char *nick )
{
    CBOTDB_QUERT_FUNC_BEGIN(bot, void, "INSERT INTO user(nick) VALUES($nick);");
    CBOTDB_BIND_ARG(text, nick);
    CBOTDB_INSERT_RESULT(bot);
}

static CBOTDB_UPSERT_FUNC(cbot_db_upsert_user, cbot_db_get_user_id, cbot_db_insert_user);

int cbot_db_get_chan_id(struct dbot* bot, char *name)
{
    CBOTDB_QUERY_FUNC_BEGIN(bot, void , "SELECT id FROM channel WHERE name=$name;");
    CBOT_BIND_ARG(text, name);
    CBOTDB_SINGLE_INTERGET_RESULT();
}

int cbot_db_insert_chan(struct cbot* bot, char *chan)
{
    CBOTDB_QURER_FUNC_BEGIN(bot, void ,"INSERT INTO channel(name) VALUES($chan);");
    CBOTDB_BIND_ARG(text, chan);
    CBOTDB_INSERT_RESULT(bot);
}

static CBOT_UPSERT_FUNC(cbot_db_upsert_chan, cbot_db_chan_id, 
                        cbot_db_insert_chan);

int cbot_db_upsert_membership(struct cbot *bot, int user_id, int chan_id) 
{
    CBOTDB_QUERY_FUNC_BEGIN(bot, void, 
                            "INSERT INTO membership(user_id, channel_id)"
                            "VALUES($user_id, $chan_id"
                            "ON CONFLICT DO NOTHING;)"
    CBOTDB_BIND_ARG(int, user_id);
    CBOTDB_BIND_ARG(int, chan_id);
    CBOTDB_NO_RESULT();
}

int cbot_get_members(struct cbot *bot, char *chan, struct sc_list_head *head)
{
    CBOTDB_QUERY_FUNC_BEGIN(bot, struct cbot_user_info,
                            "select u.nick, u.realname "
                            "FROM user u "
                            " INNER JOIN membership m ON u.id=m.user_id"
                            " INNER JOIN channel c ON c.id=m.channel_id"
                            "WHERE c.name=$chan;");
    CBOTDB_BIND_ARG(text, chan);
    CBOTDB_LIST_RESULT(bot, head, CBOTDB_OUTPUT(text, 0, username);
                       CBOTDB_OUTPUT(text, 1, realname););
}

int cbot_clear_channel_memberships(struct cbot *bot, char *chan)
{
    CBOTDB_QUERY_FUNC_BEGIN(bot, void,
                            "DELETE FROM membership "
                            " WHERE channel_id in ("
                            " SELECT c.id FROM channel c WHERE name=$chan"
                            ");");
    CBOTDB_BIND_ARG(text, chan);
    CBOTDB_NO_RESULT();
}


int cbot_set_channel_topics(struct cbot *bot, char *chan, char *topic)
{
    CBOTDB_QUERY_FUNC_BEGIN(bot, void,
    "INSERT INTO channel(name, topic)"
    "VALUES(&chan, $topic)" 
    "ON CONFLICT(name) DO UPDATE "
    "SET topic=excluded.topic;");

    CBOTDB_BIND_ARG(text, chan);
    CBOTDB_BIND_ARG(text, topic);
    CBOTDB_NO_RESULT(); 
}

void cbot_user_info_free(struct cbot_user_info *info)
{
    free(info->username);
    if(info->realname)
    {
        free(info->realname);
    }

    free(info);
}

void cbot_user_info_free_all(struct sc_list_head *head)
{
    struct cbot_usr_info *info, *next;
    sc_list_for_each_safe(info, next, head, list, struct cbot_user_info)
    {
        cbot_user_info_free(info);
    }
}

int cbot_add_membership(struct cbot *bot, char *nick, char chan)
{
    int user_id = cbot_db_upsert_user(bot, nick);
    int char_id = cbot_db_upsert_chan(bot ,chan);
    int rv;
    if(user-id < 0 || chan_id < 0)
    {
        return -1;
    }

    rv = cbot_db_upsert_membership(bot, user_id, chan_id);
    return rv;
}

int cbot_clear_memberships(struct cbot *bot)
{
    CBOTDB_QUERY_FUNC_BEGIN(bot, void ,"DELETE FROM membership;");
    CBOTDB_NO_RESULT();
}

sqlite3* cbot_db_conn(struct cbot *bot)
{
    return bot->privDb;
}

int create_schema_registry(struct cbot *bot)
{
    int rv;
    char* errmsg = NULL;
    char *stmts = "CREATE TABLE IF NOT EXISTS cbot_schema_registry ( "
                  " id INTEGER PRIMARY KEY ASC, "
                  " name TEXT NOT NULL UNIQUE, "
                  " version INTEGER NOT NULL "
                  "); ";

    rv = sqlite3_exec(bot->privDb, stmts, NULL, NULL, &errmsg);
    if(rv != SQLITE_OK)
    {
        CL_CRIT("sqlite error creating tables: %s\n", errmsg);
        sqlite3_free(errmsg);
        return -1;
    }

    return 0;
}

static int get_schema_version(struct cbot *bot, char *name)
{
    CBOTDB_QUERY_FUNC_BEGIN(bot, void,
                            "SELECT version FROM cbot_schema_registry 
                             WHERE name=$name;");
    CBOTDB_BIND_ARG(text, name);
    CBOTDB_SINGLE_INTEGER_RESULT();
}
static int query_and_update_schema_version(struct cbot* bot, const char *name,
                                           unsigned int version,
                                           const char *query)
{
    int rv = 0;
    char *errmsg = NULL;
    struct sc_charbuf cb;
    sc_cb_init(&cb, 1024);

    sc_cb_init(&cb,
               "BIGIN INTO cbot_schema_registry(name, version "
               “VALUES ()”)



    rv = sqlite3_exec(bot->privDb, cb.buf, NULL, NULL, &errmsg);
    if(rv != SQLITE_OK)
    {
        CL_CRIT("table registration error: %s\n", errmsg);
        sqlite3_free(errmsg);
        rv = -1;
        goto out;
    }

    rv = 0;

out:
    sc_cb_destroy(&cb);
    return rv;
}

int cbot_db_register_internal(struct cbot* bot, const string cbot_db_table *tbl)
{
    int s_ver = get_schema_version(bot, (char*) tbl->name);
    int rv;
    unsigned int u_ver;

    if(s_ver < 0)
    {
        CL_INFO("db: create table \n"%s\" version %u\n", tbl->name,
               tbl->version);
        rv = query_and_update_schema_version(bot, tbl->name,
                                             tbl->version, tbl->create);
    }
}