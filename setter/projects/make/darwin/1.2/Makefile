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

# Directory with main and log source files
MAINDIR  = ../../../../src

# Directory with main platform source files
SRCDIR = $(MAINDIR)/unix

# Directory with subplatform source files
PLATDIR =$(SRCDIR)/darwin

# Object files
OBJS	= $(MAINDIR)/log.o $(MAINDIR)/main.o $(SRCDIR)/attr.o $(SRCDIR)/dirdepth.o \
		  $(SRCDIR)/files.o $(SRCDIR)/links.o $(SRCDIR)/perms.o $(SRCDIR)/rsrcfork.o \
		  $(SRCDIR)/time.o $(SRCDIR)/volume.o $(SRCDIR)/xattr.o $(SRCDIR)/deleted.o \
		  $(SRCDIR)/filename.o $(SRCDIR)/frag.o $(SRCDIR)/os.o $(SRCDIR)/sparse.o \
		  $(PLATDIR)/attr.o $(PLATDIR)/os.o $(PLATDIR)/rsrcfork.o \
		  $(PLATDIR)/sparse.o $(PLATDIR)/volume.o $(PLATDIR)/xattr.o

# Source files
SOURCE	= $(MAINDIR)/log.c $(MAINDIR)/main.c $(SRCDIR)/attr.c $(SRCDIR)/dirdepth.c \
		  $(SRCDIR)/files.c $(SRCDIR)/links.c $(SRCDIR)/perms.c $(SRCDIR)/rsrcfork.c \
		  $(SRCDIR)/time.c $(SRCDIR)/volume.c $(SRCDIR)/xattr.c $(SRCDIR)/deleted.c \
		  $(SRCDIR)/filename.c $(SRCDIR)/frag.c $(SRCDIR)/os.c $(SRCDIR)/sparse.c \
		  $(PLATDIR)/attr.c $(PLATDIR)/os.c $(PLATDIR)/rsrcfork.c \
		  $(PLATDIR)/sparse.c $(PLATDIR)/volume.c $(PLATDIR)/xattr.c

# Header files
HEADER	= $(MAINDIR)/log.h $(MAINDIR)/main.h $(SRCDIR)/perms.h $(SRCDIR)/time.h \
		  $(SRCDIR)/volume.h $(PLATDIR)/attr.h $(PLATDIR)/darwin.h \
		  $(PLATDIR)/rsrcfork.h $(PLATDIR)/volume.h $(PLATDIR)/xattr.h

# Outfile
OUT	= fssetter

# Linker flags
LFLAGS	= -arch i386 -arch ppc

CFLAGS  = -DHAVE_SYS_MOUNT_H -DUSE_STATFS_FTYPENAME -DUSE_STATFS_FLAGS -arch i386 -arch ppc

all: ../1.0/fssetter

fssetter: $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c -o $@ $<

# clean house
clean:
	rm -f $(OBJS) $(OUT)
