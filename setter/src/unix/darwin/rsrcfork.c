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

#ifdef HAVE_CARBON
#include "carbon.h"
#endif

#include <errno.h>
#include <limits.h>
#include <paths.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../../log.h"
#include "rsrcfork.h"

void DarwinResourceFork(const char* path)
{
    int    ret = -1;
    char   resource_file[PATH_MAX];
    FILE*  h;
    int    rc, cRc, wRc, rRc;
    size_t written;

#ifdef HAVE_CARBON
    ret = CarbonResourceFork(path);
#endif
#ifdef _PATH_RSRCFORKSPEC

    // Correctly done by Carbon, if not fallback to _PATH_RSRCFORKSPEC
    if(ret > 0) return;

    // No subdirectory created
    if(ret < 0)
    {
        ret = chdir(path);

        if(ret)
        {
            log_write("Error %d changing to specified path.\n", errno);
            return;
        }

        ret = mkdir("RSRC", 0755);

        if(ret)
        {
            log_write("Error %d creating working directory.\n", errno);
            return;
        }

        ret = chdir("RSRC");

        if(ret)
        {
            log_write("Error %d changing to working directory.\n", errno);
            return;
        }
    }

    log_write("Creating resource forks.\n");

    // Create file
    rc  = 0;
    wRc = 0;
    cRc = 0;
    rRc = 0;
    h   = fopen("ICNS", "w+");
    if(h == NULL) rc = errno;
    else
    {
        // Write data fork
        ret = fprintf(h, "%s", icnsText);

        // Failed to write data fork, do not continue
        if(ret < 1)
        {
            wRc = errno;
            unlink("ICNS");
            fclose(h);
        }
        else
        {
            // Close the data fork
            ret = fclose(h);

            // Error closing, not continuing
            if(ret) cRc = errno;
            else
            {
                // Create resource fork
                memset(resource_file, 0, PATH_MAX);
                snprintf(resource_file, PATH_MAX, "ICNS%s", _PATH_RSRCFORKSPEC);
                h = fopen(resource_file, "w+");

                // Remove data fork as well
                if(h == NULL)
                {
                    rc = errno;
                    unlink("ICNS");
                }
                else
                {
                    // Write resource fork
                    written = fwrite(icnsData, 1, sizeof(icnsData), h);

                    if(written != sizeof(icnsData)) rRc = errno == 0 ? -1 : errno;

                    ret = fclose(h);

                    if(ret) cRc = errno;
                }
            }
        }
    }
    log_write("\tFile with an icon in the resource fork: name = \"%s\", rc = %d, wRc = %d, cRc = %d, rRc = %d\n",
              "ICNS",
              rc,
              wRc,
              cRc,
              rRc);

    // Create file
    rc  = 0;
    wRc = 0;
    cRc = 0;
    rRc = 0;
    h   = fopen("PICT", "w+");
    if(h == NULL) rc = errno;
    else
    {
        // Write data fork
        ret = fprintf(h, "%s", pictText);

        // Failed to write data fork, do not continue
        if(ret < 1)
        {
            wRc = errno;
            unlink("PICT");
            fclose(h);
        }
        else
        {
            // Close the data fork
            ret = fclose(h);

            // Error closing, not continuing
            if(ret) cRc = errno;
            else
            {
                // Create resource fork
                memset(resource_file, 0, PATH_MAX);
                snprintf(resource_file, PATH_MAX, "PICT%s", _PATH_RSRCFORKSPEC);
                h = fopen(resource_file, "w+");

                // Remove data fork as well
                if(h == NULL)
                {
                    rc = errno;
                    unlink("PICT");
                }
                else
                {
                    // Write resource fork
                    written = fwrite(pictData, 1, sizeof(pictData), h);

                    if(written != sizeof(pictData)) rRc = errno == 0 ? -1 : errno;

                    ret = fclose(h);

                    if(ret) cRc = errno;
                }
            }
        }
    }
    log_write("\tFile with an picture in the resource fork: name = \"%s\", rc = %d, wRc = %d, cRc = %d, rRc = %d\n",
              "PICT",
              rc,
              wRc,
              cRc,
              rRc);

    // Create file
    rc  = 0;
    wRc = 0;
    cRc = 0;
    rRc = 0;
    h   = fopen("VERSION", "w+");
    if(h == NULL) rc = errno;
    else
    {
        // Write data fork
        ret = fprintf(h, "%s", versText);

        // Failed to write data fork, do not continue
        if(ret < 1)
        {
            wRc = errno;
            unlink("VERSION");
            fclose(h);
        }
        else
        {
            // Close the data fork
            ret = fclose(h);

            // Error closing, not continuing
            if(ret) cRc = errno;
            else
            {
                // Create resource fork
                memset(resource_file, 0, PATH_MAX);
                snprintf(resource_file, PATH_MAX, "VERSION%s", _PATH_RSRCFORKSPEC);
                h = fopen(resource_file, "w+");

                // Remove data fork as well
                if(h == NULL)
                {
                    rc = errno;
                    unlink("VERSION");
                }
                else
                {
                    // Write resource fork
                    written = fwrite(versData, 1, sizeof(versData), h);

                    if(written != sizeof(versData)) rRc = errno == 0 ? -1 : errno;

                    ret = fclose(h);

                    if(ret) cRc = errno;
                }
            }
        }
    }
    log_write("\tFile with a version in the resource fork: name = \"%s\", rc = %d, wRc = %d, cRc = %d, rRc = %d\n",
              "VERSION",
              rc,
              wRc,
              cRc,
              rRc);

    // Create file
    rc  = 0;
    wRc = 0;
    cRc = 0;
    rRc = 0;
    h   = fopen("ALL", "w+");
    if(h == NULL) rc = errno;
    else
    {
        // Write data fork
        ret = fprintf(h, "%s", rsrcText);

        // Failed to write data fork, do not continue
        if(ret < 1)
        {
            wRc = errno;
            unlink("ALL");
            fclose(h);
        }
        else
        {
            // Close the data fork
            ret = fclose(h);

            // Error closing, not continuing
            if(ret) cRc = errno;
            else
            {
                // Create resource fork
                memset(resource_file, 0, PATH_MAX);
                snprintf(resource_file, PATH_MAX, "ALL%s", _PATH_RSRCFORKSPEC);
                h = fopen(resource_file, "w+");

                // Remove data fork as well
                if(h == NULL)
                {
                    rc = errno;
                    unlink("ALL");
                }
                else
                {
                    // Write resource fork
                    written = fwrite(rsrcData, 1, sizeof(rsrcData), h);

                    if(written != sizeof(rsrcData)) rRc = errno == 0 ? -1 : errno;

                    ret = fclose(h);

                    if(ret) cRc = errno;
                }
            }
        }
    }
    log_write("\tFile with an icon, a picture and a version in the resource fork: name = \"%s\", rc = %d, wRc = %d, "
              "cRc = %d, rRc = %d\n",
              "ALL",
              rc,
              wRc,
              cRc,
              rRc);
#endif // _PATH_RSRCFORKSPEC
}
