# Microsoft Visual C++ generated build script - Do not modify

PROJ = FSSETTER
DEBUG = 1
PROGTYPE = 2
CALLER = 
ARGS = 
DLLS = 
ORIGIN = MSVCNT
ORIGIN_VER = 1.00
PROJPATH = C:\FSTESTER\SETTER\PROJECTS\MSVC10\ 
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = DOS.C
FIRSTCPP = 
RC = rc
CFLAGS_D_DEXE32 = /nologo /G3 /W3 /Zi /YX /D "_X86_" /D "_DEBUG" /D "_CONSOLE" /FR /ML /Fd"FSSETTER.PDB" /Fp"FSSETTER.PCH"
CFLAGS_R_DEXE32 = /nologo /W3 /YX /O2 /D "_X86_" /D "NDEBUG" /D "_CONSOLE" /FR /ML /Fp"FSSETTER.PCH"
LFLAGS_D_DEXE32 = /NOLOGO /DEBUG /DEBUGTYPE:cv /SUBSYSTEM:console netapi32.lib
LFLAGS_R_DEXE32 = /NOLOGO /SUBSYSTEM:console netapi32.lib
LFLAGS_D_LIB32 = /NOLOGO
LFLAGS_R_LIB32 = /NOLOGO
LIBS_D_DEXE32 = 
LIBS_R_DEXE32 = 
RCFLAGS32 = 
D_RCDEFINES32 = -d_DEBUG
R_RCDEFINES32 = -dNDEBUG
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_DEXE32)
LFLAGS = $(LFLAGS_D_DEXE32)
LIBS = $(LIBS_D_DEXE32)
LFLAGS_LIB=$(LFLAGS_D_LIB32)
MAPFILE_OPTION = 
RCDEFINES = $(D_RCDEFINES32)
!else
CFLAGS = $(CFLAGS_R_DEXE32)
LFLAGS = $(LFLAGS_R_DEXE32)
LIBS = $(LIBS_R_DEXE32)
MAPFILE_OPTION = 
LFLAGS_LIB=$(LFLAGS_R_LIB32)
RCDEFINES = $(R_RCDEFINES32)
!endif
SBRS = MAIN.SBR \
		WIN32.SBR


MAIN_DEP =  \
	c:\fstester\setter\src\main.h \
	c:\fstester\setter\src\defs.h


WIN32_DEP =  \
	c:\fstester\setter\src\win32.h \
	c:\fstester\setter\src\consts.h \
	c:\fstester\setter\src\defs.h


all:	$(PROJ).EXE $(PROJ).BSC

MAIN.OBJ:	..\..\SRC\MAIN.C $(MAIN_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\..\SRC\MAIN.C

WIN32.OBJ:	..\..\SRC\WIN32.C $(WIN32_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c ..\..\SRC\WIN32.C

$(PROJ).EXE:	MAIN.OBJ WIN32.OBJ $(OBJS_EXT) $(LIBS_EXT)
	echo >NUL @<<$(PROJ).CRF
MAIN.OBJ 
WIN32.OBJ 
$(OBJS_EXT)
-OUT:$(PROJ).EXE
$(MAPFILE_OPTION)
$(LIBS)
$(LIBS_EXT)
$(DEFFILE_OPTION) -implib:$(PROJ).lib
<<
	link $(LFLAGS) @$(PROJ).CRF

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
