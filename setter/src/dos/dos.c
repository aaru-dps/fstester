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

#if defined(__WATCOM__)
#include <i86.h>
#include <stdlib.h>
#include <string.h>
#elif defined(__DJGPP__)
#include <dpmi.h>
#include <go32.h>
#include <sys/movedata.h>
#endif

#include "dos.h"

unsigned int _dos_getdiskfree_ex(unsigned int drive, struct diskfree_ex_t* diskspace)
{
#if defined(__WATCOM__)
    char                  drivePath[4];
    union REGS            regs;
    struct SREGS          sregs;
    struct diskfree_ex_t* copy;

    copy = malloc(sizeof(struct diskfree_ex_t));

    if(!copy)
    {
        errno = ENOMEM;
        return -1;
    }

    memcpy(copy, diskspace, sizeof(struct diskfree_ex_t));

    drivePath[0] = (drive & 0xFF) + '@';
    drivePath[1] = ':';
    drivePath[2] = '\\';
    drivePath[3] = 0;

    regs.w.ax = 0x7303;
    sregs.ds  = FP_SEG(drivePath);
    regs.w.dx = FP_OFF(drivePath);
    sregs.es  = FP_SEG(copy);
    regs.w.di = FP_OFF(copy);
    regs.w.cx = sizeof(struct diskfree_ex_t);

    int86x(0x21, &regs, &regs, &sregs);

    if(regs.h.al == 0 && !regs.w.cflag)
    {
        free(copy);
        errno = ENOSYS;
        return -1;
    }
    else if(regs.w.cflag)
    {
        free(copy);
        errno     = EINVAL;
        _doserrno = regs.w.ax;
        return -1;
    }

    memcpy(diskspace, copy, sizeof(struct diskfree_ex_t));

    free(copy);
    errno     = 0;
    _doserrno = regs.w.ax;

    return 0;
#elif defined(__DJGPP__)
    char        drivePath[4];
    __dpmi_regs regs;

    drivePath[0] = (drive & 0xFF) + '@';
    drivePath[1] = ':';
    drivePath[2] = '\\';
    drivePath[3] = 0;

    // Use transferBuffer[0] for drivePath and transferBuffer[16] for diskfree_ex_t
    dosmemput(drivePath, 0, __tb);

    regs.x.ax = 0x7303;
    regs.x.ds = __tb >> 4;
    regs.x.dx = __tb & 0x0F;
    regs.x.es = (__tb + 16) >> 4;
    regs.x.di = (__tb + 16) & 0x0F;
    regs.x.cx = sizeof(struct diskfree_ex_t);

    __dpmi_int(0x21, &regs);

    if(regs.h.al == 0 && !(regs.x.flags & 1))
    {
        errno = ENOSYS;
        return -1;
    }
    else if(regs.x.flags & 1)
    {
        errno     = EINVAL;
        _doserrno = regs.x.ax;
        return -1;
    }

    dosmemget(__tb + 16, sizeof(struct diskfree_ex_t), diskspace);

    errno     = 0;
    _doserrno = regs.x.ax;

    return 0;
#else
    errno = ENOSYS;
    return -1;
#endif
}
