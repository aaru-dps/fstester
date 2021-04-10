# Microsoft Visual C++ generated build script - Do not modify

PROJ = FSSETTER
DEBUG = 1
PROGTYPE = 6
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = E:\FSTESTER\SETTER\PROJECTS\MSVC\1.0\DOS\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = LOG.C       
FIRSTCPP =             
RC = rc
CFLAGS_D_DEXE = /nologo /W3 /Zi /Od /D "_DEBUG" /D "_DOS" /FR /Fd"FSSETTER.PDB"
CFLAGS_R_DEXE = /nologo /Gs /G2 /W3 /AM /Ox /D "NDEBUG" /D "_DOS" /FR 
LFLAGS_D_DEXE = /NOLOGO /NOI /STACK:5120 /ONERROR:NOEXE /CO 
LFLAGS_R_DEXE = /NOLOGO /NOI /STACK:5120 /ONERROR:NOEXE 
LIBS_D_DEXE = oldnames slibce 
LIBS_R_DEXE = oldnames mlibce 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_DEXE)
LFLAGS = $(LFLAGS_D_DEXE)
LIBS = $(LIBS_D_DEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_DEXE)
LFLAGS = $(LFLAGS_R_DEXE)
LIBS = $(LIBS_R_DEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = LOG.SBR \
		MAIN.SBR \
		ATTR.SBR \
		DELETED.SBR \
		DIRDEPTH.SBR \
		DOS.SBR \
		DOSUNAME.SBR \
		FILENAME.SBR \
		FILES.SBR \
		FRAG.SBR \
		LINKS.SBR \
		OS.SBR \
		PERMS.SBR \
		RSRCFORK.SBR \
		SPARSE.SBR \
		TIME.SBR \
		VOLUME.SBR \
		XATTR.SBR


LOG_DEP = e:\fstester\setter\src\log.h \
	e:\fstester\setter\src\main.h


MAIN_DEP = e:\fstester\setter\src\main.h \
	e:\fstester\setter\src\include/defs.h \
	e:\fstester\setter\src\log.h


ATTR_DEP = e:\fstester\setter\src\include/defs.h \
	e:\fstester\setter\src\log.h \
	e:\fstester\setter\src\dos\attr.h \
	e:\fstester\setter\src\dos\dosdefs.h


DELETED_DEP = e:\fstester\setter\src\include/defs.h \
	e:\fstester\setter\src\log.h \
	e:\fstester\setter\src\dos\dosdefs.h


DIRDEPTH_DEP = e:\fstester\setter\src\include/defs.h \
	e:\fstester\setter\src\log.h \
	e:\fstester\setter\src\dos\dosdefs.h


DOS_DEP = e:\fstester\setter\src\dos\dosdefs.h


DOSUNAME_DEP = e:\fstester\setter\src\dos\dosuname.h


FILENAME_DEP = e:\fstester\setter\src\include/consts.h \
	e:\fstester\setter\src\include/defs.h \
	e:\fstester\setter\src\log.h \
	e:\fstester\setter\src\dos\dosdefs.h


FILES_DEP = e:\fstester\setter\src\include/defs.h \
	e:\fstester\setter\src\log.h \
	e:\fstester\setter\src\dos\dosdefs.h


FRAG_DEP = e:\fstester\setter\src\include/consts.h \
	e:\fstester\setter\src\include/defs.h \
	e:\fstester\setter\src\log.h \
	e:\fstester\setter\src\dos\dosdefs.h


LINKS_DEP = e:\fstester\setter\src\include/defs.h


OS_DEP = e:\fstester\setter\src\include/defs.h \
	e:\fstester\setter\src\log.h \
	e:\fstester\setter\src\dos\dosuname.h


PERMS_DEP = e:\fstester\setter\src\include/defs.h


RSRCFORK_DEP = e:\fstester\setter\src\include/defs.h


SPARSE_DEP = e:\fstester\setter\src\include/defs.h


TIME_DEP = e:\fstester\setter\src\include/defs.h \
	e:\fstester\setter\src\log.h \
	e:\fstester\setter\src\dos\dosdefs.h \
	e:\fstester\setter\src\dos\dostime.h


VOLUME_DEP = e:\fstester\setter\src\include/defs.h \
	e:\fstester\setter\src\log.h \
	e:\fstester\setter\src\dos\dosdefs.h


XATTR_DEP = e:\fstester\setter\src\include/defs.h


all:	$(PROJ).EXE $(PROJ).BSC

LOG.OBJ:	..\..\..\..\SRC\LOG.C $(LOG_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c ..\..\..\..\SRC\LOG.C

MAIN.OBJ:	..\..\..\..\SRC\MAIN.C $(MAIN_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\..\..\..\SRC\MAIN.C

ATTR.OBJ:	..\..\..\..\SRC\DOS\ATTR.C $(ATTR_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\..\..\..\SRC\DOS\ATTR.C

DELETED.OBJ:	..\..\..\..\SRC\DOS\DELETED.C $(DELETED_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\..\..\..\SRC\DOS\DELETED.C

DIRDEPTH.OBJ:	..\..\..\..\SRC\DOS\DIRDEPTH.C $(DIRDEPTH_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\..\..\..\SRC\DOS\DIRDEPTH.C

DOS.OBJ:	..\..\..\..\SRC\DOS\DOS.C $(DOS_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\..\..\..\SRC\DOS\DOS.C

DOSUNAME.OBJ:	..\..\..\..\SRC\DOS\DOSUNAME.C $(DOSUNAME_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\..\..\..\SRC\DOS\DOSUNAME.C

FILENAME.OBJ:	..\..\..\..\SRC\DOS\FILENAME.C $(FILENAME_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\..\..\..\SRC\DOS\FILENAME.C

FILES.OBJ:	..\..\..\..\SRC\DOS\FILES.C $(FILES_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\..\..\..\SRC\DOS\FILES.C

FRAG.OBJ:	..\..\..\..\SRC\DOS\FRAG.C $(FRAG_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\..\..\..\SRC\DOS\FRAG.C

LINKS.OBJ:	..\..\..\..\SRC\DOS\LINKS.C $(LINKS_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\..\..\..\SRC\DOS\LINKS.C

OS.OBJ:	..\..\..\..\SRC\DOS\OS.C $(OS_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\..\..\..\SRC\DOS\OS.C

PERMS.OBJ:	..\..\..\..\SRC\DOS\PERMS.C $(PERMS_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\..\..\..\SRC\DOS\PERMS.C

RSRCFORK.OBJ:	..\..\..\..\SRC\DOS\RSRCFORK.C $(RSRCFORK_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\..\..\..\SRC\DOS\RSRCFORK.C

SPARSE.OBJ:	..\..\..\..\SRC\DOS\SPARSE.C $(SPARSE_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\..\..\..\SRC\DOS\SPARSE.C

TIME.OBJ:	..\..\..\..\SRC\DOS\TIME.C $(TIME_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\..\..\..\SRC\DOS\TIME.C

VOLUME.OBJ:	..\..\..\..\SRC\DOS\VOLUME.C $(VOLUME_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\..\..\..\SRC\DOS\VOLUME.C

XATTR.OBJ:	..\..\..\..\SRC\DOS\XATTR.C $(XATTR_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\..\..\..\SRC\DOS\XATTR.C

$(PROJ).EXE::	LOG.OBJ MAIN.OBJ ATTR.OBJ DELETED.OBJ DIRDEPTH.OBJ DOS.OBJ DOSUNAME.OBJ \
	FILENAME.OBJ FILES.OBJ FRAG.OBJ LINKS.OBJ OS.OBJ PERMS.OBJ RSRCFORK.OBJ SPARSE.OBJ \
	TIME.OBJ VOLUME.OBJ XATTR.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
LOG.OBJ +
MAIN.OBJ +
ATTR.OBJ +
DELETED.OBJ +
DIRDEPTH.OBJ +
DOS.OBJ +
DOSUNAME.OBJ +
FILENAME.OBJ +
FILES.OBJ +
FRAG.OBJ +
LINKS.OBJ +
OS.OBJ +
PERMS.OBJ +
RSRCFORK.OBJ +
SPARSE.OBJ +
TIME.OBJ +
VOLUME.OBJ +
XATTR.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
