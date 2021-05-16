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
Copyright (C) 2011-2021 Natalia Portillo
*****************************************************************************/

#include <eti.h>
#include <mint/cookie.h>
#include <mint/mintbind.h>
#include <mint/osbind.h>
#include <mint/ssystem.h>
#include <mint/sysvars.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "os.h"

#include "../include/defs.h"
#include "../log.h"

void GetOsInfo()
{
    OSHEADER*             osHeader;
    unsigned short        version;
    long**                cookieJar = _p_cookies;
    long                  cookie    = 0;
    char                  type[5];
    int                   rc;
    struct _stemu_vars*   stemu_vars;
    struct _tos2win_vars* tos2win_vars;
    MAGX_COOKIE*          magic_vars;
    int32_t               savessp;

    // Retrieve the OS data in Supervisor mode
    savessp  = Super(0L);
    osHeader = *((OSHEADER**)_sysbase);
    Super((void*)savessp);

    // Due to old AHDI bug
    osHeader = osHeader->os_beg;

    version = Sversion();

    log_write("OS information:\n");
    log_write("\tRunning under TOS %d.%02d\n", (osHeader->os_version & 0xFF00) >> 8, osHeader->os_version & 0xFF);
    log_write("\tCountry code: %d\n", osHeader->os_conf >> 1);
    log_write("\tVideo mode: %d\n", (osHeader->os_conf & 0x01) ? "PAL" : "NTSC");
    log_write("\tSystem build date: %04lX/%02lX/%02lX\n",
              osHeader->os_date & 0xFFFF,
              (osHeader->os_date & 0xFF0000) >> 16,
              (osHeader->os_date & 0xFF000000) >> 24);
    log_write("\tGEMDOS v%d.%02d\n", version >> 8, version & 0xFF);

    rc = Ssystem(-1, 0, 0);

    if(rc == E_OK)
    {
        rc = Ssystem(S_OSNAME, 0, 0);

        if(rc > 0)
        {
            memset(type, 0, 5);
            snprintf(type, 4, "%s", (char*)&rc);
            log_write("\tOS name: %s\n", type);
        }

        rc = Ssystem(S_OSXNAME, 0, 0);

        if(rc > 0)
        {
            memset(type, 0, 5);
            snprintf(type, 4, "%s", (char*)&rc);
            log_write("\tOS sub-name: %s\n", type);
        }
    }

    // Check for a cookie jar
    if(*cookieJar == 0) return;

    // KAOS TOS
    rc = Getcookie(C__T30, &cookie);
    if(rc == E_OK)
        log_write(
            "\tRunning under KAOS TOS from %04X/%02X/%02X\n", cookie & 0xFFFF, (cookie & 0xFF0000 >> 16), cookie >> 24);

    // MiNT / MultiTOS
    rc = Getcookie(C_MiNT, &cookie);
    if(rc == E_OK) log_write("\tRunning under MiNT/MultiTOS version %d.%02d\n", cookie >> 8, cookie & 0xFF);

    // oTOSis (format of cookie not known
    rc = Getcookie(0x4F544F53L, &cookie);
    if(rc == E_OK) log_write("\tRunning under oTOSis\n");

    // STEmulator
    rc = Getcookie(0x5354454DL, (long*)&stemu_vars);
    if(rc == E_OK)
        log_write("\tRunning under STEmulator version %d.%02d\n", stemu_vars->version >> 8, stemu_vars->version & 0xFF);

    // STEmulator
    rc = Getcookie(C__T2W, (long*)&tos2win_vars);
    if(rc == E_OK)
        log_write(
            "\tRunning under TOS2WIN version %X.%02X\n", tos2win_vars->version >> 8, tos2win_vars->version & 0xFF);

    // MagiC
    rc = Getcookie(C_MagX, (long*)&magic_vars);
    if(rc == E_OK)
        log_write("\tRunning under MagiC version %d.%d\n",
                  magic_vars->aesvars->version >> 8,
                  magic_vars->aesvars->version & 0xFF);

    // MagiC
    rc = Getcookie(C_MgMc, (long*)&magic_vars);
    if(rc == E_OK)
        log_write("\tRunning under MagiCMac version %d.%d\n",
                  magic_vars->aesvars->version >> 8,
                  magic_vars->aesvars->version & 0xFF);

    // MagiC
    rc = Getcookie(C_MgMx, (long*)&magic_vars);
    if(rc == E_OK)
        log_write("\tRunning under MagiCMac X version %d.%d\n",
                  magic_vars->aesvars->version >> 8,
                  magic_vars->aesvars->version & 0xFF);

    // MagiC
    rc = Getcookie(C_MgPC, (long*)&magic_vars);
    if(rc == E_OK)
        log_write("\tRunning under MagiC PC version %d.%d\n",
                  magic_vars->aesvars->version >> 8,
                  magic_vars->aesvars->version & 0xFF);
}
