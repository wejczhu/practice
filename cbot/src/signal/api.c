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