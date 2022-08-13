#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cbot/cbot.h"
#include "cbot_private.h"

static int current_log_level;
static FILE* current_log_file;

void cbot_vlog(int level, const char *format, va_list args)
{
    if(current_log_file && level >= current_log_level)
    {
        vfprintf(current_log_file, format, args);
    }
}

void cbot_log(int level, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    cbot_vlog(level, format, args);
    va_end(args);
}

void cbot_set_log_level(int level)
{
    current_log_level = level;
}

int cbot_get_log_level(void)
{
    return current_log_level;
}

void cbot_set_log_file(FILE *f)
{
    current_log_file = f;
}

struct levels
{
    char *name;
    int level;
}
