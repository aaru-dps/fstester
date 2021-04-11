# /****************************************************************************
# Aaru Data Preservation Suite
# -----------------------------------------------------------------------------
#
#     Author(s)      : Natalia Portillo
#
# --[ License ] ---------------------------------------------------------------
#      This program is free software: you can redistribute it and/or modify
#      it under the terms of the GNU General Public License as
#      published by the Free Software Foundation, either version 3 of the
#      License, or (at your option) any later version.
#
#      This program is distributed in the hope that it will be useful,
#      but WITHOUT ANY WARRANTY; without even the implied warranty of
#      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#      GNU General Public License for more details.
#
#      You should have received a copy of the GNU General Public License
#      along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# -----------------------------------------------------------------------------
# Copyright (C) 2011-2021 Natalia Portillo
# *****************************************************************************/

# This makefile is designed to use with EMX or GCC for OS/2

# Directory with main and log source files
MAINDIR  = ../../../src

# Directory with main platform source files
SRCDIR = $(MAINDIR)/os2

# Directory with subplatform source files
PLATDIR = $(SRCDIR)/32bit

# Object files
OBJS	= $(MAINDIR)/log.o $(MAINDIR)/main.o $(SRCDIR)/attr.o $(SRCDIR)/deleted.o \
		  $(SRCDIR)/dirdepth.o $(SRCDIR)/filename.o $(SRCDIR)/files.o $(SRCDIR)/frag.o \
		  $(SRCDIR)/links.o $(SRCDIR)/perms.o $(SRCDIR)/rsrcfork.o $(SRCDIR)/sparse.o \
		  $(SRCDIR)/time.o $(SRCDIR)/volume.o $(PLATDIR)/os.o $(PLATDIR)/xattr.o

# Source files
SOURCE	= $(MAINDIR)/log.c $(MAINDIR)/main.c $(SRCDIR)/attr.c $(SRCDIR)/deleted.c \
		  $(SRCDIR)/dirdepth.c $(SRCDIR)/filename.c $(SRCDIR)/files.c $(SRCDIR)/frag.c \
		  $(SRCDIR)/links.c $(SRCDIR)/perms.c $(SRCDIR)/rsrcfork.c $(SRCDIR)/sparse.c \
		  $(SRCDIR)/time.c $(SRCDIR)/volume.c $(PLATDIR)/os.c $(PLATDIR)/xattr.c

# Header files
HEADER	= $(MAINDIR)/log.h $(MAINDIR)/main.h $(SRCDIR)/attr.h $(SRCDIR)/os2defs.h

# Outfile
OUT	= fssetter.exe

# Linker flags
LFLAGS	=

# Compiler flags. This needs the definitions on how to find statfs.h as there is no autodetection
CFLAGS  =

all: fssetter

fssetter: $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c -o $@ $<

# clean house
clean:
	rm -f $(OBJS) $(OUT)
