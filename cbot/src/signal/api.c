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