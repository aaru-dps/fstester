PROJ = fssetter
PROJFILE = fssetter.mak
DEBUG = 0

PWBRMAKE  = pwbrmake
NMAKEBSC1  = set
NMAKEBSC2  = nmake
CC  = cl
CFLAGS_G  = /W2 /BATCH
CFLAGS_D  = /Gi$(PROJ).mdt /Zi /Od
CFLAGS_R  = /Ot /Oi /Ol /Oe /Og /Gs
MAPFILE_D  = NUL
MAPFILE_R  = NUL
LFLAGS_G  = /NOI /BATCH
LFLAGS_D  = /CO /FAR /PACKC
LFLAGS_R  = /EXE /FAR /PACKC
LINKER	= link
ILINK  = ilink
LRF  = echo > NUL

OBJS  = ..\..\..\SRC\LOG.obj ..\..\..\SRC\MAIN.obj ..\..\..\SRC\DOS\ATTR.obj\
	..\..\..\SRC\DOS\DELETED.obj ..\..\..\SRC\DOS\DIRDEPTH.obj\
	..\..\..\SRC\DOS\DOS.obj ..\..\..\SRC\DOS\DOSUNAME.obj\
	..\..\..\SRC\DOS\FILENAME.obj ..\..\..\SRC\DOS\FILES.obj\
	..\..\..\SRC\DOS\FRAG.obj ..\..\..\SRC\DOS\LINKS.obj\
	..\..\..\SRC\DOS\OS.obj ..\..\..\SRC\DOS\PERMS.obj\
	..\..\..\SRC\DOS\RSRCFORK.obj ..\..\..\SRC\DOS\SPARSE.obj\
	..\..\..\SRC\DOS\TIME.obj ..\..\..\SRC\DOS\VOLUME.obj\
	..\..\..\SRC\DOS\XATTR.obj
SBRS  = ..\..\..\SRC\LOG.sbr ..\..\..\SRC\MAIN.sbr ..\..\..\SRC\DOS\ATTR.sbr\
	..\..\..\SRC\DOS\DELETED.sbr ..\..\..\SRC\DOS\DIRDEPTH.sbr\
	..\..\..\SRC\DOS\DOS.sbr ..\..\..\SRC\DOS\DOSUNAME.sbr\
	..\..\..\SRC\DOS\FILENAME.sbr ..\..\..\SRC\DOS\FILES.sbr\
	..\..\..\SRC\DOS\FRAG.sbr ..\..\..\SRC\DOS\LINKS.sbr\
	..\..\..\SRC\DOS\OS.sbr ..\..\..\SRC\DOS\PERMS.sbr\
	..\..\..\SRC\DOS\RSRCFORK.sbr ..\..\..\SRC\DOS\SPARSE.sbr\
	..\..\..\SRC\DOS\TIME.sbr ..\..\..\SRC\DOS\VOLUME.sbr\
	..\..\..\SRC\DOS\XATTR.sbr

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES: .sbr .obj .c

..\..\..\SRC\LOG.obj : ..\..\..\SRC\LOG.C ..\..\..\SRC\log.h\
	..\..\..\SRC\main.h

..\..\..\SRC\LOG.sbr : ..\..\..\SRC\LOG.C ..\..\..\SRC\log.h\
	..\..\..\SRC\main.h

..\..\..\SRC\MAIN.obj : ..\..\..\SRC\MAIN.C ..\..\..\SRC\main.h\
	..\..\..\SRC\include\defs.h ..\..\..\SRC\log.h

..\..\..\SRC\MAIN.sbr : ..\..\..\SRC\MAIN.C ..\..\..\SRC\main.h\
	..\..\..\SRC\include\defs.h ..\..\..\SRC\log.h

..\..\..\SRC\DOS\ATTR.obj : ..\..\..\SRC\DOS\ATTR.C\
	..\..\..\SRC\include\defs.h ..\..\..\SRC\log.h ..\..\..\SRC\DOS\attr.h\
	..\..\..\SRC\DOS\dosdefs.h

..\..\..\SRC\DOS\ATTR.sbr : ..\..\..\SRC\DOS\ATTR.C\
	..\..\..\SRC\include\defs.h ..\..\..\SRC\log.h ..\..\..\SRC\DOS\attr.h\
	..\..\..\SRC\DOS\dosdefs.h

..\..\..\SRC\DOS\DELETED.obj : ..\..\..\SRC\DOS\DELETED.C\
	..\..\..\SRC\include\defs.h ..\..\..\SRC\log.h\
	..\..\..\SRC\DOS\dosdefs.h

..\..\..\SRC\DOS\DELETED.sbr : ..\..\..\SRC\DOS\DELETED.C\
	..\..\..\SRC\include\defs.h ..\..\..\SRC\log.h\
	..\..\..\SRC\DOS\dosdefs.h

..\..\..\SRC\DOS\DIRDEPTH.obj : ..\..\..\SRC\DOS\DIRDEPTH.C\
	..\..\..\SRC\include\defs.h ..\..\..\SRC\log.h\
	..\..\..\SRC\DOS\dosdefs.h

..\..\..\SRC\DOS\DIRDEPTH.sbr : ..\..\..\SRC\DOS\DIRDEPTH.C\
	..\..\..\SRC\include\defs.h ..\..\..\SRC\log.h\
	..\..\..\SRC\DOS\dosdefs.h

..\..\..\SRC\DOS\DOS.obj : ..\..\..\SRC\DOS\DOS.C ..\..\..\SRC\DOS\dosdefs.h

..\..\..\SRC\DOS\DOS.sbr : ..\..\..\SRC\DOS\DOS.C ..\..\..\SRC\DOS\dosdefs.h

..\..\..\SRC\DOS\DOSUNAME.obj : ..\..\..\SRC\DOS\DOSUNAME.C\
	..\..\..\SRC\DOS\dosuname.h

..\..\..\SRC\DOS\DOSUNAME.sbr : ..\..\..\SRC\DOS\DOSUNAME.C\
	..\..\..\SRC\DOS\dosuname.h

..\..\..\SRC\DOS\FILENAME.obj : ..\..\..\SRC\DOS\FILENAME.C\
	..\..\..\SRC\include\consts.h ..\..\..\SRC\include\defs.h\
	..\..\..\SRC\log.h ..\..\..\SRC\DOS\dosdefs.h

..\..\..\SRC\DOS\FILENAME.sbr : ..\..\..\SRC\DOS\FILENAME.C\
	..\..\..\SRC\include\consts.h ..\..\..\SRC\include\defs.h\
	..\..\..\SRC\log.h ..\..\..\SRC\DOS\dosdefs.h

..\..\..\SRC\DOS\FILES.obj : ..\..\..\SRC\DOS\FILES.C\
	..\..\..\SRC\include\defs.h ..\..\..\SRC\log.h\
	..\..\..\SRC\DOS\dosdefs.h

..\..\..\SRC\DOS\FILES.sbr : ..\..\..\SRC\DOS\FILES.C\
	..\..\..\SRC\include\defs.h ..\..\..\SRC\log.h\
	..\..\..\SRC\DOS\dosdefs.h

..\..\..\SRC\DOS\FRAG.obj : ..\..\..\SRC\DOS\FRAG.C\
	..\..\..\SRC\include\consts.h ..\..\..\SRC\include\defs.h\
	..\..\..\SRC\log.h ..\..\..\SRC\DOS\dosdefs.h

..\..\..\SRC\DOS\FRAG.sbr : ..\..\..\SRC\DOS\FRAG.C\
	..\..\..\SRC\include\consts.h ..\..\..\SRC\include\defs.h\
	..\..\..\SRC\log.h ..\..\..\SRC\DOS\dosdefs.h

..\..\..\SRC\DOS\LINKS.obj : ..\..\..\SRC\DOS\LINKS.C\
	..\..\..\SRC\include\defs.h

..\..\..\SRC\DOS\LINKS.sbr : ..\..\..\SRC\DOS\LINKS.C\
	..\..\..\SRC\include\defs.h

..\..\..\SRC\DOS\OS.obj : ..\..\..\SRC\DOS\OS.C ..\..\..\SRC\include\defs.h\
	..\..\..\SRC\log.h ..\..\..\SRC\DOS\dosuname.h

..\..\..\SRC\DOS\OS.sbr : ..\..\..\SRC\DOS\OS.C ..\..\..\SRC\include\defs.h\
	..\..\..\SRC\log.h ..\..\..\SRC\DOS\dosuname.h

..\..\..\SRC\DOS\PERMS.obj : ..\..\..\SRC\DOS\PERMS.C\
	..\..\..\SRC\include\defs.h

..\..\..\SRC\DOS\PERMS.sbr : ..\..\..\SRC\DOS\PERMS.C\
	..\..\..\SRC\include\defs.h

..\..\..\SRC\DOS\RSRCFORK.obj : ..\..\..\SRC\DOS\RSRCFORK.C\
	..\..\..\SRC\include\defs.h

..\..\..\SRC\DOS\RSRCFORK.sbr : ..\..\..\SRC\DOS\RSRCFORK.C\
	..\..\..\SRC\include\defs.h

..\..\..\SRC\DOS\SPARSE.obj : ..\..\..\SRC\DOS\SPARSE.C\
	..\..\..\SRC\include\defs.h

..\..\..\SRC\DOS\SPARSE.sbr : ..\..\..\SRC\DOS\SPARSE.C\
	..\..\..\SRC\include\defs.h

..\..\..\SRC\DOS\TIME.obj : ..\..\..\SRC\DOS\TIME.C\
	..\..\..\SRC\include\defs.h ..\..\..\SRC\log.h\
	..\..\..\SRC\DOS\dosdefs.h ..\..\..\SRC\DOS\dostime.h

..\..\..\SRC\DOS\TIME.sbr : ..\..\..\SRC\DOS\TIME.C\
	..\..\..\SRC\include\defs.h ..\..\..\SRC\log.h\
	..\..\..\SRC\DOS\dosdefs.h ..\..\..\SRC\DOS\dostime.h

..\..\..\SRC\DOS\VOLUME.obj : ..\..\..\SRC\DOS\VOLUME.C\
	..\..\..\SRC\include\defs.h ..\..\..\SRC\log.h\
	..\..\..\SRC\DOS\dosdefs.h

..\..\..\SRC\DOS\VOLUME.sbr : ..\..\..\SRC\DOS\VOLUME.C\
	..\..\..\SRC\include\defs.h ..\..\..\SRC\log.h\
	..\..\..\SRC\DOS\dosdefs.h

..\..\..\SRC\DOS\XATTR.obj : ..\..\..\SRC\DOS\XATTR.C\
	..\..\..\SRC\include\defs.h

..\..\..\SRC\DOS\XATTR.sbr : ..\..\..\SRC\DOS\XATTR.C\
	..\..\..\SRC\include\defs.h


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
	$(LINKER) @$(PROJ).lrf


.c.sbr :
!IF $(DEBUG)
	$(CC) /Zs $(CFLAGS_G) $(CFLAGS_D) /FR$@ $<
!ELSE
	$(CC) /Zs $(CFLAGS_G) $(CFLAGS_R) /FR$@ $<
!ENDIF

.c.obj :
!IF $(DEBUG)
	$(CC) /c $(CFLAGS_G) $(CFLAGS_D) /Fo$@ $<
!ELSE
	$(CC) /c $(CFLAGS_G) $(CFLAGS_R) /Fo$@ $<
!ENDIF


run: $(PROJ).exe
	$(PROJ).exe $(RUNFLAGS)

debug: $(PROJ).exe
	CV $(CVFLAGS) $(PROJ).exe $(RUNFLAGS)
