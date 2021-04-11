PROJ = fssetter
PROJFILE = fssetter.mak
DEBUG = 0

PWBRMAKE  = pwbrmake
NMAKEBSC1  = set
NMAKEBSC2  = nmake
CC  = cl
CFLAGS_G  = /W2 /G2 /Zp /BATCH
CFLAGS_D  = /qc /Gi$(PROJ).mdt /Zr /Zi /Od
CFLAGS_R  = /Ot /Oi /Ol /Oe /Og /Gs
MAPFILE_D  = NUL
MAPFILE_R  = NUL
LFLAGS_G  = /NOI /BATCH
LFLAGS_D  = /CO /INC /FAR /PACKC /PACKD
LFLAGS_R  = /EXE /FAR /PACKC /PACKD
LINKER	= link
ILINK  = ilink
LRF  = echo > NUL

OBJS  = ..\..\..\src\log.obj ..\..\..\src\main.obj ..\..\..\src\os2\attr.obj\
	..\..\..\src\os2\deleted.obj ..\..\..\src\os2\dirdepth.obj\
	..\..\..\src\os2\filename.obj ..\..\..\src\os2\files.obj\
	..\..\..\src\os2\frag.obj ..\..\..\src\os2\links.obj\
	..\..\..\src\os2\perms.obj ..\..\..\src\os2\rsrcfork.obj\
	..\..\..\src\os2\sparse.obj ..\..\..\src\os2\time.obj\
	..\..\..\src\os2\volume.obj ..\..\..\src\os2\16bit\os.obj\
	..\..\..\src\os2\16bit\xattr.obj
SBRS  = ..\..\..\src\log.sbr ..\..\..\src\main.sbr ..\..\..\src\os2\attr.sbr\
	..\..\..\src\os2\deleted.sbr ..\..\..\src\os2\dirdepth.sbr\
	..\..\..\src\os2\filename.sbr ..\..\..\src\os2\files.sbr\
	..\..\..\src\os2\frag.sbr ..\..\..\src\os2\links.sbr\
	..\..\..\src\os2\perms.sbr ..\..\..\src\os2\rsrcfork.sbr\
	..\..\..\src\os2\sparse.sbr ..\..\..\src\os2\time.sbr\
	..\..\..\src\os2\volume.sbr ..\..\..\src\os2\16bit\os.sbr\
	..\..\..\src\os2\16bit\xattr.sbr

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES: .obj .sbr .c

..\..\..\src\log.obj : ..\..\..\src\log.c ..\..\..\src\log.h\
	..\..\..\src\main.h

..\..\..\src\log.sbr : ..\..\..\src\log.c ..\..\..\src\log.h\
	..\..\..\src\main.h

..\..\..\src\main.obj : ..\..\..\src\main.c ..\..\..\src\main.h\
	..\..\..\src\include\defs.h ..\..\..\src\log.h

..\..\..\src\main.sbr : ..\..\..\src\main.c ..\..\..\src\main.h\
	..\..\..\src\include\defs.h ..\..\..\src\log.h

..\..\..\src\os2\attr.obj : ..\..\..\src\os2\attr.c ..\..\..\src\os2\attr.h\
	..\..\..\src\include\consts.h ..\..\..\src\include\defs.h\
	..\..\..\src\log.h ..\..\..\src\os2\os2defs.h

..\..\..\src\os2\attr.sbr : ..\..\..\src\os2\attr.c ..\..\..\src\os2\attr.h\
	..\..\..\src\include\consts.h ..\..\..\src\include\defs.h\
	..\..\..\src\log.h ..\..\..\src\os2\os2defs.h

..\..\..\src\os2\deleted.obj : ..\..\..\src\os2\deleted.c\
	..\..\..\src\include\consts.h ..\..\..\src\include\defs.h\
	..\..\..\src\log.h ..\..\..\src\os2\os2defs.h

..\..\..\src\os2\deleted.sbr : ..\..\..\src\os2\deleted.c\
	..\..\..\src\include\consts.h ..\..\..\src\include\defs.h\
	..\..\..\src\log.h ..\..\..\src\os2\os2defs.h

..\..\..\src\os2\dirdepth.obj : ..\..\..\src\os2\dirdepth.c\
	..\..\..\src\include\consts.h ..\..\..\src\include\defs.h\
	..\..\..\src\log.h ..\..\..\src\os2\os2defs.h

..\..\..\src\os2\dirdepth.sbr : ..\..\..\src\os2\dirdepth.c\
	..\..\..\src\include\consts.h ..\..\..\src\include\defs.h\
	..\..\..\src\log.h ..\..\..\src\os2\os2defs.h

..\..\..\src\os2\filename.obj : ..\..\..\src\os2\filename.c\
	..\..\..\src\include\consts.h ..\..\..\src\include\defs.h\
	..\..\..\src\log.h ..\..\..\src\os2\os2defs.h

..\..\..\src\os2\filename.sbr : ..\..\..\src\os2\filename.c\
	..\..\..\src\include\consts.h ..\..\..\src\include\defs.h\
	..\..\..\src\log.h ..\..\..\src\os2\os2defs.h

..\..\..\src\os2\files.obj : ..\..\..\src\os2\files.c\
	..\..\..\src\include\consts.h ..\..\..\src\include\defs.h\
	..\..\..\src\log.h ..\..\..\src\os2\os2defs.h

..\..\..\src\os2\files.sbr : ..\..\..\src\os2\files.c\
	..\..\..\src\include\consts.h ..\..\..\src\include\defs.h\
	..\..\..\src\log.h ..\..\..\src\os2\os2defs.h

..\..\..\src\os2\frag.obj : ..\..\..\src\os2\frag.c\
	..\..\..\src\include\consts.h ..\..\..\src\include\defs.h\
	..\..\..\src\log.h ..\..\..\src\os2\os2defs.h

..\..\..\src\os2\frag.sbr : ..\..\..\src\os2\frag.c\
	..\..\..\src\include\consts.h ..\..\..\src\include\defs.h\
	..\..\..\src\log.h ..\..\..\src\os2\os2defs.h

..\..\..\src\os2\links.obj : ..\..\..\src\os2\links.c\
	..\..\..\src\include\defs.h

..\..\..\src\os2\links.sbr : ..\..\..\src\os2\links.c\
	..\..\..\src\include\defs.h

..\..\..\src\os2\perms.obj : ..\..\..\src\os2\perms.c\
	..\..\..\src\include\defs.h

..\..\..\src\os2\perms.sbr : ..\..\..\src\os2\perms.c\
	..\..\..\src\include\defs.h

..\..\..\src\os2\rsrcfork.obj : ..\..\..\src\os2\rsrcfork.c\
	..\..\..\src\include\defs.h

..\..\..\src\os2\rsrcfork.sbr : ..\..\..\src\os2\rsrcfork.c\
	..\..\..\src\include\defs.h

..\..\..\src\os2\sparse.obj : ..\..\..\src\os2\sparse.c\
	..\..\..\src\include\consts.h ..\..\..\src\include\defs.h\
	..\..\..\src\os2\os2defs.h

..\..\..\src\os2\sparse.sbr : ..\..\..\src\os2\sparse.c\
	..\..\..\src\include\consts.h ..\..\..\src\include\defs.h\
	..\..\..\src\os2\os2defs.h

..\..\..\src\os2\time.obj : ..\..\..\src\os2\time.c\
	..\..\..\src\include\consts.h ..\..\..\src\include\defs.h\
	..\..\..\src\log.h ..\..\..\src\os2\os2defs.h

..\..\..\src\os2\time.sbr : ..\..\..\src\os2\time.c\
	..\..\..\src\include\consts.h ..\..\..\src\include\defs.h\
	..\..\..\src\log.h ..\..\..\src\os2\os2defs.h

..\..\..\src\os2\volume.obj : ..\..\..\src\os2\volume.c\
	..\..\..\src\include\consts.h ..\..\..\src\include\defs.h\
	..\..\..\src\log.h ..\..\..\src\os2\os2defs.h

..\..\..\src\os2\volume.sbr : ..\..\..\src\os2\volume.c\
	..\..\..\src\include\consts.h ..\..\..\src\include\defs.h\
	..\..\..\src\log.h ..\..\..\src\os2\os2defs.h

..\..\..\src\os2\16bit\os.obj : ..\..\..\src\os2\16bit\os.c\
	..\..\..\src\include\consts.h ..\..\..\src\include\defs.h\
	..\..\..\src\log.h ..\..\..\src\os2\os2defs.h

..\..\..\src\os2\16bit\os.sbr : ..\..\..\src\os2\16bit\os.c\
	..\..\..\src\include\consts.h ..\..\..\src\include\defs.h\
	..\..\..\src\log.h ..\..\..\src\os2\os2defs.h

..\..\..\src\os2\16bit\xattr.obj : ..\..\..\src\os2\16bit\xattr.c\
	..\..\..\src\os2\16bit\xattr.h ..\..\..\src\include\consts.h\
	..\..\..\src\include\defs.h ..\..\..\src\log.h\
	..\..\..\src\os2\os2defs.h

..\..\..\src\os2\16bit\xattr.sbr : ..\..\..\src\os2\16bit\xattr.c\
	..\..\..\src\os2\16bit\xattr.h ..\..\..\src\include\consts.h\
	..\..\..\src\include\defs.h ..\..\..\src\log.h\
	..\..\..\src\os2\os2defs.h


$(PROJ).bsc : $(SBRS)
	$(PWBRMAKE) @<<
$(BRFLAGS) $(SBRS)
<<

$(PROJ).exe : $(OBJS)
!IF $(DEBUG)
	$(LRF) @<<$(PROJ).lrf
$(RT_OBJS: = +^
) $(OBJS: = +^
)
$@
$(MAPFILE_D)
$(LLIBS_G: = +^
) +
$(LLIBS_D: = +^
) +
$(LIBS: = +^
)
$(DEF_FILE) $(LFLAGS_G) $(LFLAGS_D);
<<
!ELSE
	$(LRF) @<<$(PROJ).lrf
$(RT_OBJS: = +^
) $(OBJS: = +^
)
$@
$(MAPFILE_R)
$(LLIBS_G: = +^
) +
$(LLIBS_R: = +^
) +
$(LIBS: = +^
)
$(DEF_FILE) $(LFLAGS_G) $(LFLAGS_R);
<<
!ENDIF
!IF $(DEBUG)
	$(ILINK) -a -e "$(LINKER) @$(PROJ).lrf" $@
!ELSE
	$(LINKER) @$(PROJ).lrf
!ENDIF


.c.obj :
!IF $(DEBUG)
	$(CC) /c $(CFLAGS_G) $(CFLAGS_D) /Fo$@ $<
!ELSE
	$(CC) /c $(CFLAGS_G) $(CFLAGS_R) /Fo$@ $<
!ENDIF

.c.sbr :
!IF $(DEBUG)
	$(CC) /Zs $(CFLAGS_G) $(CFLAGS_D) /FR$@ $<
!ELSE
	$(CC) /Zs $(CFLAGS_G) $(CFLAGS_R) /FR$@ $<
!ENDIF


run: $(PROJ).exe
	$(PROJ).exe $(RUNFLAGS)

debug: $(PROJ).exe
	CVP $(CVFLAGS) $(PROJ).exe $(RUNFLAGS)
