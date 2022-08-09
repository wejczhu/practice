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

