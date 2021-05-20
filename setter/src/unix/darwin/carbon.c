//
// Created by claunia on 16/3/21.
//

#include <Carbon/Carbon.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/syslimits.h>
#include <unistd.h>

#include "carbon.h"

#include "../../log.h"
#include "rsrcfork.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

int CarbonResourceFork(const char* path)
{
    int               ret;
    unsigned char*    absolute_path;
    OSStatus          err;
    FSRef             parentDirRef;
    TextToUnicodeInfo oTextToUnicodeInfo;
    UniChar           iconUnicodeStr[256];
    ByteCount         iconUnicodeLen = 0;
    UniChar           pictUnicodeStr[256];
    ByteCount         pictUnicodeLen = 0;
    UniChar           versionUnicodeStr[256];
    ByteCount         versionUnicodeLen = 0;
    UniChar           allUnicodeStr[256];
    ByteCount         allUnicodeLen = 0;
    ByteCount         unicodeRead;
    HFSUniStr255      resourceForkName;
    int               count = -1; // Not even tried to write a resource fork
    OSErr             rc, rRc;
    FSRef             fileRef;
    ResFileRefNum     rsrcRef;
    Handle            h;
    FILE*             f;
    size_t            txtLen, written;
    int               wRc, cRc;

    memset(&oTextToUnicodeInfo, 0, sizeof(TextToUnicodeInfo));

    err = CreateTextToUnicodeInfoByEncoding(kTextEncodingMacRoman, &oTextToUnicodeInfo);

    if(err)
    {
        log_write("Error %d getting MacRoman to Unicode converter.\n", err);

        return count;
    }

    err = ConvertFromTextToUnicode(
        oTextToUnicodeInfo, 4, "ICNS", 0, 0, NULL, NULL, NULL, 256, &unicodeRead, &iconUnicodeLen, iconUnicodeStr);

    if(err)
    {
        log_write("Error %d converting \"ICNS\" to Unicode.\n", err);

        return count;
    }

    if(unicodeRead < 4)
    {
        log_write("Needed to read 4 bytes to convert \"ICNS\" to Unicode but read %d bytes.\n", unicodeRead);

        return count;
    }

    err = ConvertFromTextToUnicode(
        oTextToUnicodeInfo, 4, "PICT", 0, 0, NULL, NULL, NULL, 256, &unicodeRead, &pictUnicodeLen, pictUnicodeStr);

    if(err)
    {
        log_write("Error %d converting \"PICT\" to Unicode.\n", err);

        return count;
    }

    if(unicodeRead < 4)
    {
        log_write("Needed to read 4 bytes to convert \"PICT\" to Unicode but read %d bytes.\n", unicodeRead);

        return count;
    }

    err = ConvertFromTextToUnicode(oTextToUnicodeInfo,
                                   7,
                                   "VERSION",
                                   0,
                                   0,
                                   NULL,
                                   NULL,
                                   NULL,
                                   256,
                                   &unicodeRead,
                                   &versionUnicodeLen,
                                   versionUnicodeStr);

    if(err)
    {
        log_write("Error %d converting \"VERSION\" to Unicode.\n", err);

        return count;
    }

    if(unicodeRead < 7)
    {
        log_write("Needed to read 7 bytes to convert \"VERSION\" to Unicode but read %d bytes.\n", unicodeRead);

        return count;
    }

    err = ConvertFromTextToUnicode(
        oTextToUnicodeInfo, 3, "ALL", 0, 0, NULL, NULL, NULL, 256, &unicodeRead, &allUnicodeLen, allUnicodeStr);

    if(err)
    {
        log_write("Error %d converting \"ALL\" to Unicode.\n", err);

        return count;
    }

    if(unicodeRead < 3)
    {
        log_write("Needed to read 4 bytes to convert \"ALL\" to Unicode but read %d bytes.\n", unicodeRead);

        return count;
    }

    err = FSGetResourceForkName(&resourceForkName);

    if(err)
    {
        log_write("Error %d trying to get resource fork name.\n", err);

        return count;
    }

    ret = chdir(path);

    if(ret)
    {
        log_write("Error %d changing to specified path.\n", errno);
        return count;
    }

    ret = mkdir("RSRC", 0755);

    if(ret)
    {
        log_write("Error %d creating working directory.\n", errno);
        return count;
    }

    absolute_path = (unsigned char*)realpath("RSRC", NULL);

    if(absolute_path == NULL)
    {
        log_write("Error getting working directory absolute path.\n", errno);

        ret = rmdir("RSRC");

        return ret ? -1 : 0;
    }

    ret = chdir("RSRC");

    if(ret)
    {
        log_write("Error %d changing to working directory.\n", errno);

        ret = rmdir("RSRC");

        return ret ? -1 : 0;
    }

    count++; // Set to 0, we can start

    memset(&parentDirRef, 0, sizeof(FSRef));

    err = FSPathMakeRef(absolute_path, &parentDirRef, NULL);

    if(err)
    {
        log_write("Error %d getting filesystem reference from path.\n", err);

        return count;
    }

    log_write("Creating resource forks.\n");

    rc = FSCreateResourceFile(&parentDirRef,
                              iconUnicodeLen,
                              iconUnicodeStr,
                              kFSCatInfoNone,
                              NULL,
                              resourceForkName.length,
                              resourceForkName.unicode,
                              &fileRef,
                              NULL);

    rRc = 0;
    wRc = 0;
    cRc = 0;

    if(!rc)
    {
        rRc = FSOpenResourceFile(&fileRef, resourceForkName.length, resourceForkName.unicode, fsRdWrPerm, &rsrcRef);

        if(!rRc)
        {
            h = NewHandle(ICNS_RESOURCE_SIZE);

            if(h)
            {
                memcpy(h, IcnsResource, ICNS_RESOURCE_SIZE);
                AddResource(h, rtIcons, -16455, IcnsResourceNamePascal);
                WriteResource(h);
                ReleaseResource(h);

                UpdateResFile(rsrcRef);
                CloseResFile(rsrcRef);

                count++;

                f = fopen("ICNS", "w+");

                if(f != NULL)
                {
                    txtLen  = strlen(icnsText);
                    written = fwrite(icnsText, txtLen, 1, f);

                    wRc = written != txtLen ? errno : 0;
                    cRc = fclose(f);
                }
                else
                    rc = errno;
            }
        }
    }

    log_write("\tFile with an icon in the resource fork: name = \"%s\", rc = %d, wRc = %d, cRc = %d, rRc = %d\n",
              "ICNS",
              rc,
              wRc,
              cRc,
              rRc);

    rc = FSCreateResourceFile(&parentDirRef,
                              pictUnicodeLen,
                              pictUnicodeStr,
                              kFSCatInfoNone,
                              NULL,
                              resourceForkName.length,
                              resourceForkName.unicode,
                              &fileRef,
                              NULL);

    rRc = 0;
    wRc = 0;
    cRc = 0;

    if(!rc)
    {
        rRc = FSOpenResourceFile(&fileRef, resourceForkName.length, resourceForkName.unicode, fsRdWrPerm, &rsrcRef);

        if(!rRc)
        {
            h = NewHandle(PICT_RESOURCE_SIZE);

            if(h)
            {
                memcpy(h, PictResource, PICT_RESOURCE_SIZE);
                AddResource(h, ftPICTFile, 29876, PictResourceNamePascal);
                WriteResource(h);
                ReleaseResource(h);

                UpdateResFile(rsrcRef);
                CloseResFile(rsrcRef);

                count++;

                f = fopen("PICT", "w+");

                if(f != NULL)
                {
                    txtLen  = strlen(pictText);
                    written = fwrite(pictText, txtLen, 1, f);

                    wRc = written != txtLen ? errno : 0;
                    cRc = fclose(f);
                }
                else
                    rc = errno;
            }
        }
    }

    log_write("\tFile with an picture in the resource fork: name = \"%s\", rc = %d, wRc = %d, cRc = %d, rRc = %d\n",
              "PICT",
              rc,
              wRc,
              cRc,
              rRc);

    rc = FSCreateResourceFile(&parentDirRef,
                              versionUnicodeLen,
                              versionUnicodeStr,
                              kFSCatInfoNone,
                              NULL,
                              resourceForkName.length,
                              resourceForkName.unicode,
                              &fileRef,
                              NULL);

    rRc = 0;
    wRc = 0;
    cRc = 0;

    if(!rc)
    {
        rRc = FSOpenResourceFile(&fileRef, resourceForkName.length, resourceForkName.unicode, fsRdWrPerm, &rsrcRef);

        if(!rRc)
        {
            h = NewHandle(VERS_RESOURCE_SIZE);

            if(h)
            {
                memcpy(h, VersResource, VERS_RESOURCE_SIZE);
                AddResource(h, rtVersion, 1, VersResourceNamePascal);
                WriteResource(h);
                ReleaseResource(h);

                UpdateResFile(rsrcRef);
                CloseResFile(rsrcRef);

                count++;

                f = fopen("VERSION", "w+");

                if(f != NULL)
                {
                    txtLen  = strlen(versText);
                    written = fwrite(versText, txtLen, 1, f);

                    wRc = written != txtLen ? errno : 0;
                    cRc = fclose(f);
                }
                else
                    rc = errno;
            }
        }
    }

    log_write("\tFile with a version in the resource fork: name = \"%s\", rc = %d, wRc = %d, cRc = %d, rRc = %d\n",
              "VERSION",
              rc,
              wRc,
              cRc,
              rRc);

    rc = FSCreateResourceFile(&parentDirRef,
                              allUnicodeLen,
                              allUnicodeStr,
                              kFSCatInfoNone,
                              NULL,
                              resourceForkName.length,
                              resourceForkName.unicode,
                              &fileRef,
                              NULL);

    rRc = 0;
    wRc = 0;
    cRc = 0;

    if(!rc)
    {
        rRc = FSOpenResourceFile(&fileRef, resourceForkName.length, resourceForkName.unicode, fsRdWrPerm, &rsrcRef);

        if(!rRc)
        {
            h = NewHandle(ICNS_RESOURCE_SIZE);

            if(h)
            {
                memcpy(h, IcnsResource, ICNS_RESOURCE_SIZE);
                AddResource(h, rtIcons, -16455, IcnsResourceNamePascal);
                WriteResource(h);
                ReleaseResource(h);

                count++;
            }

            h = NewHandle(PICT_RESOURCE_SIZE);

            if(h)
            {
                memcpy(h, PictResource, PICT_RESOURCE_SIZE);
                AddResource(h, ftPICTFile, -16455, PictResourceNamePascal);
                WriteResource(h);
                ReleaseResource(h);

                count++;
            }

            h = NewHandle(VERS_RESOURCE_SIZE);

            if(h)
            {
                memcpy(h, VersResource, VERS_RESOURCE_SIZE);
                AddResource(h, rtVersion, 1, VersResourceNamePascal);
                WriteResource(h);
                ReleaseResource(h);

                count++;
            }

            UpdateResFile(rsrcRef);
            CloseResFile(rsrcRef);

            f = fopen("ALL", "w+");

            if(f != NULL)
            {
                txtLen  = strlen(rsrcText);
                written = fwrite(rsrcText, txtLen, 1, f);

                wRc = written != txtLen ? errno : 0;
                cRc = fclose(f);
            }
            else
                rc = errno;
        }
    }

    log_write("\tFile with an icon, a picture and a version in the resource fork: name = \"%s\", rc = %d, wRc = %d, "
              "cRc = %d, rRc = %d\n",
              "ALL",
              rc,
              wRc,
              cRc,
              rRc);

    return count;
}

#pragma clang diagnostic pop
