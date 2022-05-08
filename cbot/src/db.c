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
}