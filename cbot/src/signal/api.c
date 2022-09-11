#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cbot/cbot.h"
#include "internal.h"
#include "nosj.h"
#include "sc-colletions.h"

void sig_user_free(struct signal_user *user)
{
    if(user)
    {
        free(user->first_name);
        free(user->number);
        free(user->uuid);
        free(user);
    }
}

void sig_user_free_all(struct sc_list_head *list)
{
    struct signal_user *user, *next;
    sc_list_for_each_safe(user, next, lit, list, struct signal_user)
    {
        sc_list_remove(&user->list);
        sig_user_free(user);
    }
}

static struct signal_user *__sig_parse_profile(struct jmsg *jm, size_t ix)
{
    struct signal_user *user;
    char *nul;
    size_t namelen;

    user = malloc(sizeof(*user));
    sc_list_init(&user->list);
    user->first_name = jmsg_lookup_string_at_len(jm, ix, "name", &namelen);
    if(user->first_name)
    {
        nul = strchr(user->first_name, '\0');
        if((nul - user->first_name) < namelen)
        {
            user->last_name = nul + 1;
        }
        else
        {
            user->last_name = NULL;
        }
    }

    user->number = jmsg_lookup_string_at(jm, ix, "address.number");
    user->uuid = jmsg_lookup_string_at(jm, ix, "address.uuid");

    return user;
}