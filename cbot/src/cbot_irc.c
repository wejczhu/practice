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