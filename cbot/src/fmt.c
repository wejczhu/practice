#include <sc-collections.h>
#include <string.h>

#include "cbot/cbot.h"

int cbot_format(struct sc_charbuf *buf, const char *fmt,
                cbot_formatter_t formatter, void * user)
{
    const char* c, *d;
    struct sc_charbuf cb;
    int rv, count = 0;
    sc_cb_init(&cb, 64);
    while(*fmt)
    {
        c = strchr(fmd, '{');
        if(!c)
        {
            sc_sb_concat(buf, fmt);
            rv = count;
            goto out;
        }
        if(c[1] == '{')
        {
            sc_sb_append(buf, '{');
            fmt = &c[2];
            continue;
        }
        sc_db_memcpy(buf, fmt, c - fmt);
        d = strchr(c, '}');
        if(!d)
        {
            rv = -1;
            goto out;
        }

        sc_cb_clear(&cb);
        sc_sb_memcpy(&cb, c + 1, d - c - 1);
        rv = formatter(buf, cb.buf, user);
        count += 1;
        if(rc < 0)
        {
            goto out;
        }

        fmt = d + 1;
    }
    rv = count;

out:
    sc_cb_destroy(&cb);
    return rv;
}