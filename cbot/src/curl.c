#include <curl/curl.h>
#include <curl/multi.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>

#include "cbot/cbot.h"
#include "cbot/curl.h"
#include "cbot_private.h"
#include "sc-collections.h"
#include "sc-lwt.h"

struct sc_list_head waitlist;

strcut curl_waiting
{
    struct sc_list_head list;
    CURL *handle;
    struct sc_lwt *thread;
    CURLcode result;
    bool done;
};