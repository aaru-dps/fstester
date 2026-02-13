/****************************************************************************
Aaru Data Preservation Suite
-----------------------------------------------------------------------------

    Author(s)      : Natalia Portillo

--[ License ] ---------------------------------------------------------------
     This program is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as
     published by the Free Software Foundation, either version 3 of the
     License, or (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program.  If not, see <http://www.gnu.org/licenses/>.

-----------------------------------------------------------------------------
Copyright (C) 2011-2026 Natalia Portillo
*****************************************************************************/

#include <errno.h>
#include <stdio.h>
#include <time.h>

#if defined(__STDC__)
/* ANSI / ISO C */
#include <stdarg.h>
#define USE_ANSI_VARARGS 1
#else
/* XENIX / K&R C */
#include <varargs.h>
#endif

#include "log.h"
#include "main.h"

/* Thanks XENIX */
#if !defined(__STDC__) && !defined(COHERENT)
typedef long time_t;
#endif

static int log_opened;
static int log_quiet;
FILE*      log_file;

#if defined(__STDC__)
int log_open(int quiet)
#else
int log_open(quiet)

int quiet;
#endif
{
    time_t curtime;

    log_opened = 0;
    log_quiet  = 0;

    curtime = time(NULL);

    log_file = fopen("fssetter.log", "a+");

    if(log_file == NULL)
    {
        fprintf(stderr, "Error %d opening log.\n", errno);
        return 1;
    }

    fprintf(log_file, "Aaru Filesystem Tester (Setter) %s\n", AARU_FSTESTER_VERSION);
    fprintf(log_file, "%s\n", AARU_COPYRIGHT);
    fprintf(log_file, "==============================================\n");
    fprintf(log_file, "Log started on %s\n\n", asctime(gmtime(&curtime)));
    fflush(log_file);

    log_opened = 1;
    log_quiet  = quiet;

    return 0;
}

#if USE_ANSI_VARARGS

/* ANSI version */
void log_write(const char* fmt, ...)
{
    va_list args;

    if(log_opened)
    {
        va_start(args, fmt);
        vfprintf(log_file, fmt, args);
        va_end(args);
        fflush(log_file);
    }

    if(!log_quiet)
    {
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
    }
}

#else

/* XENIX K&R varargs version */
void log_write(va_alist)

va_dcl {
    va_list args;
    char *fmt;

    va_start(args);
    fmt = va_arg(args, char *);

    if (log_opened) {
        vfprintf(log_file, fmt, args);
        fflush(log_file);
    }

    /* Restart varargs for console output */
    va_end(args);
    va_start(args);
    fmt = va_arg(args, char *);

    if (!log_quiet)
        vprintf(fmt, args);

    va_end(args);
}

#endif /* USE_ANSI_VARARGS */

void log_close()
{
    time_t curtime;
    if(!log_opened) return;

    curtime = time(NULL);

    fprintf(log_file, "==============================================\n");
    fprintf(log_file, "Log finished on %s\n", asctime(gmtime(&curtime)));
    fprintf(log_file, "==============================================\n\n");

    fclose(log_file);

    log_file   = NULL;
    log_opened = 0;
    log_quiet  = 0;
}

#if defined(__STDC__)
void log_set_quiet(int quiet)
#else
void log_set_quiet(quiet)

int quiet;
#endif
{
    log_file  = NULL;
    log_quiet = quiet;
}
