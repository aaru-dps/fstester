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

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/utsname.h>

#include "../log.h"

void DarwinGetOsInfo()
{
    struct utsname buf;
    int            ret;
    struct stat    finder;
    struct stat    server;
    int            macosx;
    int            macosx_server;
    int            major = 0, minor = 0, release = 0;
    char           sysname[256];
    char           sysversion[256];

    ret = uname(&buf);

    if(ret)
    {
        log_write("Error %d retrieving OS information.\n", errno);
        return;
    }

    // Darwin does not have Finder, Mac OS X does
    // TODO: Mac OS X Server 1.x
    memset(&finder, 0, sizeof(struct stat));
    ret    = stat("/System/Library/CoreServices/Finder.app", &finder);
    macosx = ret == 0;

    memset(&server, 0, sizeof(struct stat));
    ret           = stat("/System/Library/CoreServices/ServerVersion.plist", &server);
    macosx_server = ret == 0;

    memset(sysname, 0, 256);
    memset(sysversion, 0, 256);

    memcpy(sysname, buf.sysname, strlen(buf.sysname));
    memcpy(sysversion, buf.release, strlen(buf.release));

    if(macosx)
    {
        sscanf(buf.release, "%d.%d.%d", &major, &minor, &release);

        memset(sysname, 0, 256);
        sprintf(sysname, "%s", macosx_server ? "Mac OS X Server" : "Mac OS X");

        switch(major)
        {
            case 0:
                if(minor == 2)
                {
                    memset(sysname, 0, 256);
                    memset(sysversion, 0, 256);

                    sprintf(sysname, "Mac OS X Server");
                    sprintf(sysversion, "1.0.1");

                    break;
                }

                break;
            case 1:
                switch(minor)
                {
                    case 0:
                        memset(sysversion, 0, 256);
                        sprintf(sysversion, "Developer Preview 3");

                        break;
                    case 1:
                        memset(sysversion, 0, 256);
                        sprintf(sysversion, "Developer Preview 4");

                        break;
                    case 2:
                        if(release == 1)
                        {
                            memset(sysversion, 0, 256);
                            sprintf(sysversion, "Public Beta");
                        }

                        break;
                    case 3:
                        if(release == 1)
                        {
                            memset(sysversion, 0, 256);
                            sprintf(sysversion, "\"Cheetah\" 10.0");
                        }

                        break;
                    case 4:
                        if(release == 1)
                        {
                            memset(sysversion, 0, 256);
                            sprintf(sysversion, "\"Puma\" 10.1");
                        }

                        break;
                }

                break;
            case 5:
                memset(sysname, 0, 256);
                sprintf(sysname, "%s", macosx_server ? "Mac OS X Server \"Puma\"" : "Mac OS X \"Puma\"");
                memset(sysversion, 0, 256);
                sprintf(sysversion, "10.1.%d", minor);

                break;
            case 6:
                memset(sysname, 0, 256);
                sprintf(sysname, "%s", macosx_server ? "Mac OS X Server \"Jaguar\"" : "Mac OS X \"Jaguar\"");
                memset(sysversion, 0, 256);
                if(minor > 0) sprintf(sysversion, "10.2.%d", minor);
                else
                    sprintf(sysversion, "10.2");

                break;
            case 7:
                memset(sysname, 0, 256);
                sprintf(sysname, "%s", macosx_server ? "Mac OS X Server \"Panther\"" : "Mac OS X \"Panther\"");
                memset(sysversion, 0, 256);
                if(minor > 0) sprintf(sysversion, "10.3.%d", minor);
                else
                    sprintf(sysversion, "10.3");

                break;
            case 8:
                memset(sysname, 0, 256);
                sprintf(sysname, "%s", macosx_server ? "Mac OS X Server \"Tiger\"" : "Mac OS X \"Tiger\"");
                memset(sysversion, 0, 256);
                if(minor > 0) sprintf(sysversion, "10.4.%d", minor);
                else
                    sprintf(sysversion, "10.4");

                break;
            case 9:
                memset(sysname, 0, 256);
                sprintf(sysname, "%s", macosx_server ? "Mac OS X Server \"Leopard\"" : "Mac OS X \"Leopard\"");
                memset(sysversion, 0, 256);
                if(minor > 0) sprintf(sysversion, "10.5.%d", minor);
                else
                    sprintf(sysversion, "10.5");

                break;
            case 10:
                memset(sysname, 0, 256);
                sprintf(
                    sysname, "%s", macosx_server ? "Mac OS X Server \"Snow Leopard\"" : "Mac OS X \"Snow Leopard\"");
                memset(sysversion, 0, 256);
                if(minor > 0) sprintf(sysversion, "10.6.%d", minor);
                else
                    sprintf(sysversion, "10.6");

                break;
            case 11:
                memset(sysname, 0, 256);
                sprintf(sysname, "Mac OS X \"Lion\"");
                memset(sysversion, 0, 256);
                if(minor > 0) sprintf(sysversion, "10.7.%d", minor);
                else
                    sprintf(sysversion, "10.7");

                break;
            case 12:
                memset(sysname, 0, 256);
                sprintf(sysname, "OS X \"Mountain Lion\"");
                memset(sysversion, 0, 256);
                if(minor > 0) sprintf(sysversion, "10.8.%d", minor);
                else
                    sprintf(sysversion, "10.8");

                break;
            case 13:
                memset(sysname, 0, 256);
                sprintf(sysname, "OS X \"Mavericks\"");
                memset(sysversion, 0, 256);
                if(minor > 0) sprintf(sysversion, "10.9.%d", minor);
                else
                    sprintf(sysversion, "10.9");

                break;
            case 14:
                memset(sysname, 0, 256);
                sprintf(sysname, "OS X \"Yosemite\"");
                memset(sysversion, 0, 256);
                if(minor > 0) sprintf(sysversion, "10.10.%d", minor);
                else
                    sprintf(sysversion, "10.10");

                break;
            case 15:
                memset(sysname, 0, 256);
                sprintf(sysname, "OS X \"El Capitan\"");
                memset(sysversion, 0, 256);
                if(minor > 0) sprintf(sysversion, "10.11.%d", minor);
                else
                    sprintf(sysversion, "10.11");

                break;
            case 16:
                memset(sysname, 0, 256);
                sprintf(sysname, "macOS \"Sierra\"");
                memset(sysversion, 0, 256);
                if(minor > 0) sprintf(sysversion, "10.12.%d", minor);
                else
                    sprintf(sysversion, "10.12");

                break;
            case 17:
                memset(sysname, 0, 256);
                sprintf(sysname, "macOS \"High Sierra\"");
                memset(sysversion, 0, 256);
                if(minor > 0) sprintf(sysversion, "10.13.%d", minor);
                else
                    sprintf(sysversion, "10.13");

                break;
            case 18:
                memset(sysname, 0, 256);
                sprintf(sysname, "macOS \"Mojave\"");
                memset(sysversion, 0, 256);
                if(minor > 0) sprintf(sysversion, "10.14.%d", minor);
                else
                    sprintf(sysversion, "10.14");

                break;
            case 19:
                memset(sysname, 0, 256);
                sprintf(sysname, "macOS \"Catalina\"");
                memset(sysversion, 0, 256);
                if(minor > 0) sprintf(sysversion, "10.15.%d", minor);
                else
                    sprintf(sysversion, "10.15");

                break;
            case 20:
                memset(sysname, 0, 256);
                sprintf(sysname, "macOS \"Big Sur\"");
                memset(sysversion, 0, 256);
                if(minor > 0) sprintf(sysversion, "11.%d", minor);
                else
                    sprintf(sysversion, "11");

                break;
        }
    }

    log_write("OS information:\n");
    log_write("\t%s %s\n", sysname, sysversion);
    log_write("\tKernel version: %s\n", buf.version);
    log_write("\tArchitecture: %s\n", buf.machine);
}
