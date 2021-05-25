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

# cc65
CC = cl65

# Directory with main and log source files
MAINDIR  = ../../../src

# Directory with main platform source files
SRCDIR = $(MAINDIR)/8bit

# Directory with subplatform source files
PLATDIR =

# Object files
OBJS	= $(SRCDIR)/dirdepth.o $(SRCDIR)/filename.o $(SRCDIR)/files.o $(SRCDIR)/main.o

# Source files
SOURCE	= $(SRCDIR)/dirdepth.c $(SRCDIR)/filename.c $(SRCDIR)/files.c $(SRCDIR)/main.c

# Header files
HEADER	= $(MAINDIR)/main.h

# Outfile
OUT	= fssetter

apple2: CFLAGS = -t apple2 -DUSE_FOLDERS
apple2: LFLAGS = -t apple2
apple2: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

apple2e: CFLAGS = -t apple2enh -DUSE_FOLDERS
apple2e: LFLAGS = -t apple2enh
apple2e: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

atari: CFLAGS = -t atari -DUSE_FOLDERS
atari: LFLAGS = -t atari
atari: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

atarixl: CFLAGS = -t atarixl -DUSE_FOLDERS
atarixl: LFLAGS = -t atarixl
atarixl: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

c16: CFLAGS = -t c16
c16: LFLAGS = -t c16
c16: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

c64: CFLAGS = -t c64
c64: LFLAGS = -t c64
c64: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

c128: CFLAGS = -t c128
c128: LFLAGS = -t c128
c128: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

pet: CFLAGS = -t pet
pet: LFLAGS = -t pet
pet: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

plus4: CFLAGS = -t plus4
plus4: LFLAGS = -t plus4
plus4: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c -o $@ $<

# clean house
clean:
	rm -f $(OBJS)
