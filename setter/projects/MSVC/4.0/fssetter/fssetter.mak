# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=fssetter - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to fssetter - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "fssetter - Win32 Release" && "$(CFG)" !=\
 "fssetter - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "fssetter.mak" CFG="fssetter - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "fssetter - Win32 Release" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "fssetter - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "fssetter - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\fssetter.exe"

CLEAN : 
	-@erase "$(INTDIR)\attr.obj"
	-@erase "$(INTDIR)\deleted.obj"
	-@erase "$(INTDIR)\dirdepth.obj"
	-@erase "$(INTDIR)\filename.obj"
	-@erase "$(INTDIR)\files.obj"
	-@erase "$(INTDIR)\frag.obj"
	-@erase "$(INTDIR)\links.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\os.obj"
	-@erase "$(INTDIR)\perms.obj"
	-@erase "$(INTDIR)\rsrcfork.obj"
	-@erase "$(INTDIR)\sparse.obj"
	-@erase "$(INTDIR)\time.obj"
	-@erase "$(INTDIR)\volume.obj"
	-@erase "$(INTDIR)\xattr.obj"
	-@erase "$(OUTDIR)\fssetter.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/fssetter.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/fssetter.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/fssetter.pdb" /machine:I386 /out:"$(OUTDIR)/fssetter.exe" 
LINK32_OBJS= \
	"$(INTDIR)\attr.obj" \
	"$(INTDIR)\deleted.obj" \
	"$(INTDIR)\dirdepth.obj" \
	"$(INTDIR)\filename.obj" \
	"$(INTDIR)\files.obj" \
	"$(INTDIR)\frag.obj" \
	"$(INTDIR)\links.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\os.obj" \
	"$(INTDIR)\perms.obj" \
	"$(INTDIR)\rsrcfork.obj" \
	"$(INTDIR)\sparse.obj" \
	"$(INTDIR)\time.obj" \
	"$(INTDIR)\volume.obj" \
	"$(INTDIR)\xattr.obj"

"$(OUTDIR)\fssetter.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "fssetter - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\fssetter.exe"

CLEAN : 
	-@erase "$(INTDIR)\attr.obj"
	-@erase "$(INTDIR)\deleted.obj"
	-@erase "$(INTDIR)\dirdepth.obj"
	-@erase "$(INTDIR)\filename.obj"
	-@erase "$(INTDIR)\files.obj"
	-@erase "$(INTDIR)\frag.obj"
	-@erase "$(INTDIR)\links.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\os.obj"
	-@erase "$(INTDIR)\perms.obj"
	-@erase "$(INTDIR)\rsrcfork.obj"
	-@erase "$(INTDIR)\sparse.obj"
	-@erase "$(INTDIR)\time.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\volume.obj"
	-@erase "$(INTDIR)\xattr.obj"
	-@erase "$(OUTDIR)\fssetter.exe"
	-@erase "$(OUTDIR)\fssetter.ilk"
	-@erase "$(OUTDIR)\fssetter.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /Fp"$(INTDIR)/fssetter.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/fssetter.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/fssetter.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/fssetter.exe" 
LINK32_OBJS= \
	"$(INTDIR)\attr.obj" \
	"$(INTDIR)\deleted.obj" \
	"$(INTDIR)\dirdepth.obj" \
	"$(INTDIR)\filename.obj" \
	"$(INTDIR)\files.obj" \
	"$(INTDIR)\frag.obj" \
	"$(INTDIR)\links.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\os.obj" \
	"$(INTDIR)\perms.obj" \
	"$(INTDIR)\rsrcfork.obj" \
	"$(INTDIR)\sparse.obj" \
	"$(INTDIR)\time.obj" \
	"$(INTDIR)\volume.obj" \
	"$(INTDIR)\xattr.obj"

"$(OUTDIR)\fssetter.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "fssetter - Win32 Release"
# Name "fssetter - Win32 Debug"

!IF  "$(CFG)" == "fssetter - Win32 Release"

!ELSEIF  "$(CFG)" == "fssetter - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=\fstester\setter\src\main.h

!IF  "$(CFG)" == "fssetter - Win32 Release"

!ELSEIF  "$(CFG)" == "fssetter - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\fstester\setter\src\log.h

!IF  "$(CFG)" == "fssetter - Win32 Release"

!ELSEIF  "$(CFG)" == "fssetter - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\fstester\setter\src\main.c
DEP_CPP_MAIN_=\
	"..\..\..\..\src\include\defs.h"\
	"..\..\..\..\src\log.h"\
	"..\..\..\..\src\main.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\fstester\setter\src\log.c
DEP_CPP_LOG_C=\
	"..\..\..\..\src\log.h"\
	"..\..\..\..\src\main.h"\
	

"$(INTDIR)\log.obj" : $(SOURCE) $(DEP_CPP_LOG_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\fstester\setter\src\win32\xattr.c
DEP_CPP_XATTR=\
	"..\..\..\..\src\include\defs.h"\
	"..\..\..\..\src\log.h"\
	"..\..\..\..\src\win32\win32.h"\
	"..\..\..\..\src\win32\xattr.h"\
	

"$(INTDIR)\xattr.obj" : $(SOURCE) $(DEP_CPP_XATTR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\fstester\setter\src\win32\deleted.c
DEP_CPP_DELET=\
	"..\..\..\..\src\include\defs.h"\
	"..\..\..\..\src\log.h"\
	"..\..\..\..\src\win32\win32.h"\
	

"$(INTDIR)\deleted.obj" : $(SOURCE) $(DEP_CPP_DELET) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\fstester\setter\src\win32\dirdepth.c
DEP_CPP_DIRDE=\
	"..\..\..\..\src\include\defs.h"\
	"..\..\..\..\src\log.h"\
	"..\..\..\..\src\win32\win32.h"\
	

"$(INTDIR)\dirdepth.obj" : $(SOURCE) $(DEP_CPP_DIRDE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\fstester\setter\src\win32\filename.c
DEP_CPP_FILEN=\
	"..\..\..\..\src\include\consts.h"\
	"..\..\..\..\src\include\defs.h"\
	"..\..\..\..\src\log.h"\
	"..\..\..\..\src\win32\win32.h"\
	

"$(INTDIR)\filename.obj" : $(SOURCE) $(DEP_CPP_FILEN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\fstester\setter\src\win32\files.c
DEP_CPP_FILES=\
	"..\..\..\..\src\include\defs.h"\
	"..\..\..\..\src\log.h"\
	"..\..\..\..\src\win32\win32.h"\
	

"$(INTDIR)\files.obj" : $(SOURCE) $(DEP_CPP_FILES) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\fstester\setter\src\win32\frag.c
DEP_CPP_FRAG_=\
	"..\..\..\..\src\include\consts.h"\
	"..\..\..\..\src\include\defs.h"\
	"..\..\..\..\src\log.h"\
	"..\..\..\..\src\win32\win32.h"\
	

"$(INTDIR)\frag.obj" : $(SOURCE) $(DEP_CPP_FRAG_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\fstester\setter\src\win32\links.c
DEP_CPP_LINKS=\
	"..\..\..\..\src\include\defs.h"\
	"..\..\..\..\src\log.h"\
	"..\..\..\..\src\win32\links.h"\
	"..\..\..\..\src\win32\win32.h"\
	

"$(INTDIR)\links.obj" : $(SOURCE) $(DEP_CPP_LINKS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\fstester\setter\src\win32\os.c
DEP_CPP_OS_C12=\
	"..\..\..\..\src\include\defs.h"\
	"..\..\..\..\src\log.h"\
	"..\..\..\..\src\win32\os.h"\
	"..\..\..\..\src\win32\win32.h"\
	

"$(INTDIR)\os.obj" : $(SOURCE) $(DEP_CPP_OS_C12) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\fstester\setter\src\win32\perms.c
DEP_CPP_PERMS=\
	"..\..\..\..\src\include\defs.h"\
	

"$(INTDIR)\perms.obj" : $(SOURCE) $(DEP_CPP_PERMS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\fstester\setter\src\win32\rsrcfork.c
DEP_CPP_RSRCF=\
	"..\..\..\..\src\include\defs.h"\
	"..\..\..\..\src\log.h"\
	"..\..\..\..\src\win32\rsrcfork.h"\
	"..\..\..\..\src\win32\win32.h"\
	

"$(INTDIR)\rsrcfork.obj" : $(SOURCE) $(DEP_CPP_RSRCF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\fstester\setter\src\win32\sparse.c
DEP_CPP_SPARS=\
	"..\..\..\..\src\include\consts.h"\
	"..\..\..\..\src\include\defs.h"\
	"..\..\..\..\src\log.h"\
	"..\..\..\..\src\win32\sparse.h"\
	"..\..\..\..\src\win32\win32.h"\
	

"$(INTDIR)\sparse.obj" : $(SOURCE) $(DEP_CPP_SPARS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\fstester\setter\src\win32\time.c
DEP_CPP_TIME_=\
	"..\..\..\..\src\include\defs.h"\
	"..\..\..\..\src\log.h"\
	"..\..\..\..\src\win32\timew32.h"\
	"..\..\..\..\src\win32\win32.h"\
	

"$(INTDIR)\time.obj" : $(SOURCE) $(DEP_CPP_TIME_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\fstester\setter\src\win32\volume.c
DEP_CPP_VOLUM=\
	"..\..\..\..\src\include\defs.h"\
	"..\..\..\..\src\log.h"\
	"..\..\..\..\src\win32\volume.h"\
	"..\..\..\..\src\win32\win32.h"\
	

"$(INTDIR)\volume.obj" : $(SOURCE) $(DEP_CPP_VOLUM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\fstester\setter\src\win32\attr.c
DEP_CPP_ATTR_=\
	"..\..\..\..\src\include\defs.h"\
	"..\..\..\..\src\log.h"\
	"..\..\..\..\src\win32\attr.h"\
	"..\..\..\..\src\win32\win32.h"\
	

"$(INTDIR)\attr.obj" : $(SOURCE) $(DEP_CPP_ATTR_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
