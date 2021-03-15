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

#ifndef AARU_FSTESTER_SETTER_SRC_LINUX_VOLUME_H_
#define AARU_FSTESTER_SETTER_SRC_LINUX_VOLUME_H_

#ifndef ST_RDONLY
#define ST_RDONLY 1
#endif

#ifndef ST_NOSUID
#define ST_NOSUID 2
#endif

#ifndef ST_NODEV
#define ST_NODEV 4
#endif

#ifndef ST_NOEXEC
#define ST_NOEXEC 8
#endif

#ifndef ST_SYNCHRONOUS
#define ST_SYNCHRONOUS 16
#endif

#ifndef ST_MANDLOCK
#define ST_MANDLOCK 64
#endif

#ifndef ST_WRITE
#define ST_WRITE 128
#endif

#ifndef ST_APPEND
#define ST_APPEND 256
#endif

#ifndef ST_IMMUTABLE
#define ST_IMMUTABLE 512
#endif

#ifndef ST_NOATIME
#define ST_NOATIME 1024
#endif

#ifndef ST_NODIRATIME
#define ST_NODIRATIME 2048
#endif

#endif // AARU_FSTESTER_SETTER_SRC_LINUX_VOLUME_H_
