# ---------------------------------------------------------------------------
VERSION = BCB.01
# ---------------------------------------------------------------------------
!ifndef BCB
BCB = $(MAKEDIR)\..
!endif
# ---------------------------------------------------------------------------
PROJECT = fssetter.exe
OBJFILES = fssetter.obj \fstester\setter\src\main.obj \
   \fstester\setter\src\log.obj \fstester\setter\src\win32\attr.obj \
   \fstester\setter\src\win32\deleted.obj \fstester\setter\src\win32\dirdepth.obj \
   \fstester\setter\src\win32\filename.obj \fstester\setter\src\win32\files.obj \
   \fstester\setter\src\win32\frag.obj \fstester\setter\src\win32\links.obj \
   \fstester\setter\src\win32\os.obj \fstester\setter\src\win32\perms.obj \
   \fstester\setter\src\win32\rsrcfork.obj \fstester\setter\src\win32\sparse.obj \
   \fstester\setter\src\win32\time.obj \fstester\setter\src\win32\volume.obj \
   \fstester\setter\src\win32\xattr.obj
RESFILES = 
RESDEPEN = $(RESFILES)
LIBFILES = 
DEFFILE = 
# ---------------------------------------------------------------------------
CFLAG1 = -Od -Hc -w -k -r- -y -v -vi- -c -a4 -b- -w-par -w-inl -Vx -Ve -x
CFLAG2 = -Id:\fstester\setter\src\win32;d:\fstester\setter\src;$(BCB)\include;$(BCB)\include\vcl \
   -H=$(BCB)\lib\vcld.csm 
PFLAGS = -Ud:\fstester\setter\src\win32;d:\fstester\setter\src;$(BCB)\lib\obj;$(BCB)\lib \
   -Id:\fstester\setter\src\win32;d:\fstester\setter\src;$(BCB)\include;$(BCB)\include\vcl \
   -AWinTypes=Windows;WinProcs=Windows;DbiTypes=BDE;DbiProcs=BDE;DbiErrs=BDE -v \
   -$Y -$W -$O- -JPHNV -M     
RFLAGS = -id:\fstester\setter\src\win32;d:\fstester\setter\src;$(BCB)\include;$(BCB)\include\vcl 
LFLAGS = -Ld:\fstester\setter\src\win32;d:\fstester\setter\src;$(BCB)\lib\obj;$(BCB)\lib \
   -ap -Tpe -x -v -V4.0 
IFLAGS = 
LINKER = ilink32
# ---------------------------------------------------------------------------
ALLOBJ = c0x32.obj $(OBJFILES)
ALLRES = $(RESFILES)
ALLLIB = $(LIBFILES) vcl.lib import32.lib cp32mt.lib 
# ---------------------------------------------------------------------------
.autodepend

$(PROJECT): $(OBJFILES) $(RESDEPEN) $(DEFFILE)
    $(BCB)\BIN\$(LINKER) @&&!
    $(LFLAGS) +
    $(ALLOBJ), +
    $(PROJECT),, +
    $(ALLLIB), +
    $(DEFFILE), +
    $(ALLRES) 
!

.pas.hpp:
    $(BCB)\BIN\dcc32 $(PFLAGS) { $** }

.pas.obj:
    $(BCB)\BIN\dcc32 $(PFLAGS) { $** }

.cpp.obj:
    $(BCB)\BIN\bcc32 $(CFLAG1) $(CFLAG2) -o$* $* 

.c.obj:
    $(BCB)\BIN\bcc32 $(CFLAG1) $(CFLAG2) -o$* $**

.rc.res:
    $(BCB)\BIN\brcc32 $(RFLAGS) $<
#-----------------------------------------------------------------------------
