ORIGIN = PWB
ORIGIN_VER = 2.1.49
PROJ = FSTESTER
PROJFILE = FSTESTER.MAK
DEBUG = 0

CC  = cl
CFLAGS_G  = /W2 /BATCH
CFLAGS_D  = /f /Od /Zi
CFLAGS_R  = /f- /Ot /Ol /Og /Oe /Oi /Gs
CXX  = cl
CXXFLAGS_G  = /W2 /BATCH
CXXFLAGS_D  = /f /Zi /Od
CXXFLAGS_R  = /f- /Ot /Oi /Ol /Oe /Og /Gs
MAPFILE_D  = NUL
MAPFILE_R  = NUL
LFLAGS_G  = /NOI /BATCH /ONERROR:NOEXE
LFLAGS_D  = /CO /FAR /PACKC
LFLAGS_R  = /EXE /FAR /PACKC
LINKER	= link
ILINK  = ilink
LRF  = echo > NUL
ILFLAGS  = /a /e

FILES  = ..\..\SRC\LOG.C ..\..\SRC\MAIN.C ..\..\SRC\DOS\ATTR.C\
	..\..\SRC\DOS\DELETED.C ..\..\SRC\DOS\DIRDEPTH.C ..\..\SRC\DOS\DOS.C\
	..\..\SRC\DOS\DOSUNAME.C ..\..\SRC\DOS\FILENAME.C\
	..\..\SRC\DOS\FILES.C ..\..\SRC\DOS\FRAG.C ..\..\SRC\DOS\LINKS.C\
	..\..\SRC\DOS\OS.C ..\..\SRC\DOS\PERMS.C ..\..\SRC\DOS\RSRCFORK.C\
	..\..\SRC\DOS\SPARSE.C ..\..\SRC\DOS\TIME.C ..\..\SRC\DOS\VOLUME.C\
	..\..\SRC\DOS\XATTR.C
OBJS  = ..\..\SRC\LOG.obj ..\..\SRC\MAIN.obj ..\..\SRC\DOS\ATTR.obj\
	..\..\SRC\DOS\DELETED.obj ..\..\SRC\DOS\DIRDEPTH.obj\
	..\..\SRC\DOS\DOS.obj ..\..\SRC\DOS\DOSUNAME.obj\
	..\..\SRC\DOS\FILENAME.obj ..\..\SRC\DOS\FILES.obj\
	..\..\SRC\DOS\FRAG.obj ..\..\SRC\DOS\LINKS.obj ..\..\SRC\DOS\OS.obj\
	..\..\SRC\DOS\PERMS.obj ..\..\SRC\DOS\RSRCFORK.obj\
	..\..\SRC\DOS\SPARSE.obj ..\..\SRC\DOS\TIME.obj\
	..\..\SRC\DOS\VOLUME.obj ..\..\SRC\DOS\XATTR.obj

all: $(PROJ).exe

.SUFFIXES:
.SUFFIXES:
.SUFFIXES: .obj .c

..\..\SRC\LOG.obj : ..\..\SRC\LOG.C ..\..\SRC\log.h ..\..\SRC\main.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo..\..\SRC\LOG.obj ..\..\SRC\LOG.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo..\..\SRC\LOG.obj ..\..\SRC\LOG.C
<<
!ENDIF

..\..\SRC\MAIN.obj : ..\..\SRC\MAIN.C ..\..\SRC\main.h\
	..\..\SRC\include\defs.h ..\..\SRC\log.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo..\..\SRC\MAIN.obj ..\..\SRC\MAIN.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo..\..\SRC\MAIN.obj ..\..\SRC\MAIN.C
<<
!ENDIF

..\..\SRC\DOS\ATTR.obj : ..\..\SRC\DOS\ATTR.C ..\..\SRC\include\defs.h\
	..\..\SRC\log.h ..\..\SRC\DOS\attr.h ..\..\SRC\DOS\dosdefs.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo..\..\SRC\DOS\ATTR.obj ..\..\SRC\DOS\ATTR.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo..\..\SRC\DOS\ATTR.obj ..\..\SRC\DOS\ATTR.C
<<
!ENDIF

..\..\SRC\DOS\DELETED.obj : ..\..\SRC\DOS\DELETED.C ..\..\SRC\include\defs.h\
	..\..\SRC\log.h ..\..\SRC\DOS\dosdefs.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo..\..\SRC\DOS\DELETED.obj ..\..\SRC\DOS\DELETED.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo..\..\SRC\DOS\DELETED.obj ..\..\SRC\DOS\DELETED.C
<<
!ENDIF

..\..\SRC\DOS\DIRDEPTH.obj : ..\..\SRC\DOS\DIRDEPTH.C ..\..\SRC\include\defs.h\
	..\..\SRC\log.h ..\..\SRC\DOS\dosdefs.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo..\..\SRC\DOS\DIRDEPTH.obj ..\..\SRC\DOS\DIRDEPTH.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo..\..\SRC\DOS\DIRDEPTH.obj ..\..\SRC\DOS\DIRDEPTH.C
<<
!ENDIF

..\..\SRC\DOS\DOS.obj : ..\..\SRC\DOS\DOS.C ..\..\SRC\DOS\dosdefs.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo..\..\SRC\DOS\DOS.obj ..\..\SRC\DOS\DOS.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo..\..\SRC\DOS\DOS.obj ..\..\SRC\DOS\DOS.C
<<
!ENDIF

..\..\SRC\DOS\DOSUNAME.obj : ..\..\SRC\DOS\DOSUNAME.C ..\..\SRC\DOS\dosuname.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo..\..\SRC\DOS\DOSUNAME.obj ..\..\SRC\DOS\DOSUNAME.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo..\..\SRC\DOS\DOSUNAME.obj ..\..\SRC\DOS\DOSUNAME.C
<<
!ENDIF

..\..\SRC\DOS\FILENAME.obj : ..\..\SRC\DOS\FILENAME.C\
	..\..\SRC\include\consts.h ..\..\SRC\include\defs.h ..\..\SRC\log.h\
	..\..\SRC\DOS\dosdefs.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo..\..\SRC\DOS\FILENAME.obj ..\..\SRC\DOS\FILENAME.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo..\..\SRC\DOS\FILENAME.obj ..\..\SRC\DOS\FILENAME.C
<<
!ENDIF

..\..\SRC\DOS\FILES.obj : ..\..\SRC\DOS\FILES.C ..\..\SRC\include\defs.h\
	..\..\SRC\log.h ..\..\SRC\DOS\dosdefs.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo..\..\SRC\DOS\FILES.obj ..\..\SRC\DOS\FILES.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo..\..\SRC\DOS\FILES.obj ..\..\SRC\DOS\FILES.C
<<
!ENDIF

..\..\SRC\DOS\FRAG.obj : ..\..\SRC\DOS\FRAG.C ..\..\SRC\include\consts.h\
	..\..\SRC\include\defs.h ..\..\SRC\log.h ..\..\SRC\DOS\dosdefs.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo..\..\SRC\DOS\FRAG.obj ..\..\SRC\DOS\FRAG.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo..\..\SRC\DOS\FRAG.obj ..\..\SRC\DOS\FRAG.C
<<
!ENDIF

..\..\SRC\DOS\LINKS.obj : ..\..\SRC\DOS\LINKS.C ..\..\SRC\include\defs.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo..\..\SRC\DOS\LINKS.obj ..\..\SRC\DOS\LINKS.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo..\..\SRC\DOS\LINKS.obj ..\..\SRC\DOS\LINKS.C
<<
!ENDIF

..\..\SRC\DOS\OS.obj : ..\..\SRC\DOS\OS.C ..\..\SRC\include\defs.h\
	..\..\SRC\log.h ..\..\SRC\DOS\dosuname.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo..\..\SRC\DOS\OS.obj ..\..\SRC\DOS\OS.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo..\..\SRC\DOS\OS.obj ..\..\SRC\DOS\OS.C
<<
!ENDIF

..\..\SRC\DOS\PERMS.obj : ..\..\SRC\DOS\PERMS.C ..\..\SRC\include\defs.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo..\..\SRC\DOS\PERMS.obj ..\..\SRC\DOS\PERMS.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo..\..\SRC\DOS\PERMS.obj ..\..\SRC\DOS\PERMS.C
<<
!ENDIF

..\..\SRC\DOS\RSRCFORK.obj : ..\..\SRC\DOS\RSRCFORK.C ..\..\SRC\include\defs.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo..\..\SRC\DOS\RSRCFORK.obj ..\..\SRC\DOS\RSRCFORK.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo..\..\SRC\DOS\RSRCFORK.obj ..\..\SRC\DOS\RSRCFORK.C
<<
!ENDIF

..\..\SRC\DOS\SPARSE.obj : ..\..\SRC\DOS\SPARSE.C ..\..\SRC\include\defs.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo..\..\SRC\DOS\SPARSE.obj ..\..\SRC\DOS\SPARSE.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo..\..\SRC\DOS\SPARSE.obj ..\..\SRC\DOS\SPARSE.C
<<
!ENDIF

..\..\SRC\DOS\TIME.obj : ..\..\SRC\DOS\TIME.C ..\..\SRC\include\defs.h\
	..\..\SRC\log.h ..\..\SRC\DOS\dosdefs.h ..\..\SRC\DOS\dostime.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo..\..\SRC\DOS\TIME.obj ..\..\SRC\DOS\TIME.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo..\..\SRC\DOS\TIME.obj ..\..\SRC\DOS\TIME.C
<<
!ENDIF

..\..\SRC\DOS\VOLUME.obj : ..\..\SRC\DOS\VOLUME.C ..\..\SRC\include\defs.h\
	..\..\SRC\log.h ..\..\SRC\DOS\dosdefs.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo..\..\SRC\DOS\VOLUME.obj ..\..\SRC\DOS\VOLUME.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo..\..\SRC\DOS\VOLUME.obj ..\..\SRC\DOS\VOLUME.C
<<
!ENDIF

..\..\SRC\DOS\XATTR.obj : ..\..\SRC\DOS\XATTR.C ..\..\SRC\include\defs.h
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo..\..\SRC\DOS\XATTR.obj ..\..\SRC\DOS\XATTR.C
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo..\..\SRC\DOS\XATTR.obj ..\..\SRC\DOS\XATTR.C
<<
!ENDIF


$(PROJ).exe : $(OBJS)
!IF $(DEBUG)
	$(LRF) @<<$(PROJ).lrf
$(RT_OBJS: = +^
) $(OBJS: = +^
)
$@
$(MAPFILE_D)
$(LIBS: = +^
) +
$(LLIBS_G: = +^
) +
$(LLIBS_D: = +^
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
$(LIBS: = +^
) +
$(LLIBS_G: = +^
) +
$(LLIBS_R: = +^
)
$(DEF_FILE) $(LFLAGS_G) $(LFLAGS_R);
<<
!ENDIF
	$(LINKER) @$(PROJ).lrf


.c.obj :
!IF $(DEBUG)
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_D) /Fo$@ $<
<<
!ELSE
	@$(CC) @<<$(PROJ).rsp
/c $(CFLAGS_G)
$(CFLAGS_R) /Fo$@ $<
<<
!ENDIF


run: $(PROJ).exe
	$(PROJ).exe $(RUNFLAGS)

debug: $(PROJ).exe
	CV $(CVFLAGS) $(PROJ).exe $(RUNFLAGS)
