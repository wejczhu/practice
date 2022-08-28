#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cbot_private.h"

int main(int argc, char *argv[])
{
    struct cbot *bot;
    int rv;
    sranc(time(NULL));

    if(argc != 2)
    {
        printf("usage: %s CONFIG_FILE\n");
        return EXIT_FAILURE;
    }

    curl_global_init(0);

    bot = cbot_create();
    if(!bot)
    {
        return EXIT_FAILURE;
    }

    rv = cbot_load_config(bot ,argv[1]);
    if(rc < 0)
    {
        return EXIT_FAILURE;
    }

    cbot_run(bot);
    cbot_delete(bot);

    return EXIT_SUCCESS;
}