ORIGIN		= Symantec C++
ORIGIN_VER	= Version 6.10
VERSION		= DEBUG

PROJ		= FSSETTER
APPTYPE		= DOS EXE
PROJTYPE	= EXE

CC		= SC
MAKE		= MAKE
RC		= RCC
HC		= HC
ASM		= SC
DISASM		= OBJ2ASM
EXE2BIN		= EXE2BIN
LIBR		= IMPLIB
LNK		= LINK
CVPK		= CVPACK

DLLS		= 

HEADERS		= ..\..\..\..\src\dos\../include/consts.h ..\..\..\..\src\dos\../include/defs.h ..\..\..\..\src\dos\../log.h  \
		..\..\..\..\src\dos\attr.h ..\..\..\..\src\dos\dosdefs.h ..\..\..\..\src\dos\dostime.h ..\..\..\..\src\dos\dosuname.h  \
		..\..\..\..\src\include/defs.h ..\..\..\..\src\log.h ..\..\..\..\src\main.h 

LIBS		= 

DEFFILE		= FSSETTER.DEF

CFLAGS		=  -Jm -ms -C -0 -c -g 
HFLAGS		= $(CFLAGS) 
LFLAGS		=  /CO /LI 
MFLAGS		= MASTERPROJ=$(PROJ) 
RESFLAGS	=  
DEBUGGERFLAGS	=  -LOADSYMBOLS 
IMPLIBFLAGS	=  -IMPLIB -DLL 
CVPKFLAGS	=  -c 
AFLAGS		= $(CFLAGS) 
HELPFLAGS	= 

MODEL		= S

PAR		= PROJS BATS OBJS

DEFINES		= 
RCDEFINES	= 
LIBDIRS		= 
INCLUDES	= 

OBJS		=  ..\..\..\..\src\dos\attr.OBJ  ..\..\..\..\src\dos\deleted.OBJ  ..\..\..\..\src\dos\dirdepth.OBJ  \
		 ..\..\..\..\src\dos\dos.OBJ  ..\..\..\..\src\dos\dosuname.OBJ  ..\..\..\..\src\dos\filename.OBJ  ..\..\..\..\src\dos\files.OBJ  \
		 ..\..\..\..\src\dos\frag.OBJ  ..\..\..\..\src\dos\links.OBJ  ..\..\..\..\src\log.OBJ  ..\..\..\..\src\main.OBJ  \
		 ..\..\..\..\src\dos\os.OBJ  ..\..\..\..\src\dos\perms.OBJ  ..\..\..\..\src\dos\rsrcfork.OBJ  ..\..\..\..\src\dos\sparse.OBJ  \
		 ..\..\..\..\src\dos\time.OBJ  ..\..\..\..\src\dos\volume.OBJ  ..\..\..\..\src\dos\xattr.OBJ 

RCFILES		= 

RESFILES	= 

SYMS		= 

HELPFILES	= 

BATS		=  

.C.OBJ:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -o$*.obj $*.c

.CPP.OBJ:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -o$*.obj $*.cpp

.CXX.OBJ:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -o$*.obj $*.cxx

.CP.OBJ:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -o$*.obj $*.cp

.H.SYM:
	$(CC) $(HFLAGS) $(DEFINES) $(INCLUDES) -HF -o$*.sym $*.h

.HPP.SYM:
	$(CC) $(HFLAGS) $(DEFINES) $(INCLUDES) -HF -o$*.sym $*.hpp

.HXX.SYM:
	$(CC) $(HFLAGS) $(DEFINES) $(INCLUDES) -HF -o$*.sym $*.hxx

.C.EXP:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -e $*.c -l$*.lst

.CPP.EXP:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -e $*.cpp -l$*.lst

.CXX.EXP:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -e $*.cxx -l$*.lst

.CP.EXP:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -e $*.cp -l$*.lst

.ASM.EXP:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -e $*.asm -l$*.lst

.OBJ.COD:
	$(DISASM) $*.OBJ >$*.cod

.EXE.COD:
	$(DISASM) $*.EXE >$*.cod

.COM.COD:
	$(DISASM) $*.COM >$*.cod

.OBJ.EXE:
	$(LNK) $(LFLAGS) @$(PROJ).LNK

.EXE.COM:
	$(EXE2BIN) $*.EXE $*.COM

.DLL.LIB:
	$(LIBR) $*.LIB $*.DLL

.RTF.HLP:
	$(HC) $(HELPFLAGS) $*.HPJ

.ASM.OBJ:
	$(ASM) $(AFLAGS) $(DEFINES) $(INCLUDES) -o$*.obj $*.asm

.RC.RES: 
	$(RC) $(RCDEFINES) $(RESFLAGS) $(INCLUDES) $*.rc

.DLG.RES:
	echo \#include "windows.h" >$$$*.rc
	echo \#include "$*.h" >>$$$*.rc
	echo \#include "$*.dlg" >>$$$*.rc
	$(RC) $(RCDEFINES) $(RESFLAGS) $$$*.rc
	-del $*.res
	-ren $$$*.res $*.res



all:		$(PROJ).$(PROJTYPE) $(POSTLINK) done

$(PROJ).$(PROJTYPE):	$(PRECOMPILE) $(OBJS) $(RCFILES) $(RESFILES) $(HELPFILES) $(POSTCOMPILE) 
			$(LNK) $(LFLAGS) @$(PROJ).LNK
			$(CVPK) $$SCW$$.$(PROJTYPE) $(CVPKFLAGS)
			-del $(PROJ).$(PROJTYPE)
			-ren $$SCW$$.$(PROJTYPE) $(PROJ).$(PROJTYPE)
			-echo $(PROJ).$(PROJTYPE) built

done:
		-echo $(PROJ).$(PROJTYPE) done

buildall:	clean	all


clean:
		-del $(PROJ).$(PROJTYPE)
		-del SCPH.SYM
		-del ..\..\..\..\src\dos\attr.OBJ
		-del ..\..\..\..\src\dos\deleted.OBJ
		-del ..\..\..\..\src\dos\dirdepth.OBJ
		-del ..\..\..\..\src\dos\dos.OBJ
		-del ..\..\..\..\src\dos\dosuname.OBJ
		-del ..\..\..\..\src\dos\filename.OBJ
		-del ..\..\..\..\src\dos\files.OBJ
		-del ..\..\..\..\src\dos\frag.OBJ
		-del ..\..\..\..\src\dos\links.OBJ
		-del ..\..\..\..\src\log.OBJ
		-del ..\..\..\..\src\main.OBJ
		-del ..\..\..\..\src\dos\os.OBJ
		-del ..\..\..\..\src\dos\perms.OBJ
		-del ..\..\..\..\src\dos\rsrcfork.OBJ
		-del ..\..\..\..\src\dos\sparse.OBJ
		-del ..\..\..\..\src\dos\time.OBJ
		-del ..\..\..\..\src\dos\volume.OBJ
		-del ..\..\..\..\src\dos\xattr.OBJ

cleanres:

res:		cleanres $(RCFILES) all


link:
		$(LNK) $(LFLAGS) @$(PROJ).LNK
		$(CVPK) $$SCW$$.$(PROJTYPE) $(CVPKFLAGS)
		-del $(PROJ).$(PROJTYPE)
		-ren $$SCW$$.$(PROJTYPE) $(PROJ).$(PROJTYPE)




include FSSETTER.dep

