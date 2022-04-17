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

CURLcode cbot_curl_perform(struct cbot *bot, CURL *handle)
{
    struct curl_waiting wait;
    bool first = true;
    wait.handle = handle;
    wait.done =false;
    wait.thread = sc_lwt_current();
    sc_list_init(&wait.list);
    curl_easy_setopt(handle, CURLOPT_PRIVATE, (char*)&wait);
    curl_multi_add_handle(bot->curlm, handle);
    sc_lwt_set_state(bot->curl_lwt, SC_LWT_RUNNABLE);
    sc_list_insert_end(&waitlist, &wait.list);
    while(!wait.done)
    {
        CL_DEBUG("curl: %s request, yielding\n", first ? "enqueded" : "continue");
        first = false;

        sc_lwt_set_state(wait.thread, SC_LWT_BLOCKED);
        sc_lwt_yield();
        CL_DEBUG("curl: wakeup, done? %s\n", wait.done? "yes" : "no");
    }

    return wait.result;

};

void cbot_curl_run(void *data)
{
    struct cbot *bot = data;
    struct sc_lwt *cur = sc_lwt_current();
    struct curl_waiting *waiting, *next;
    struct timespec ts;
    int nhdl, maxfd;
    long millis;
    bool block;
    fd_set_in_fd, out_fd, err_fd;
    CURLMcode rv;
    CURLMsg *msg;

    bot->curl_lwt = cur;
    sc_list_init(&waitlist);

    while(true)
    {
        sc_lwt_fdgen_advance(cur);
        sc_lwt_clear_fds(&in_fd, &err_fd);
        maxfd = 0;
        curl_multi_fdset(bot->curlm, &in_fd, &out_fd, &err_fd, &maxfd);
        
    }

}
