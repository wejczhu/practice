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