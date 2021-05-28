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

# z88dk
CC = zcc

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

adam: CFLAGS = +cpm
adam: LFLAGS = +cpm -subtype=adam -create-app
adam: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

amstrad_cpc: CFLAGS = +cpc
amstrad_cpc: LFLAGS = +cpc -lcpcfs -subtype=dsk -create-app
amstrad_cpc: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

amstrad_cpm: CFLAGS = +cpm
amstrad_cpm: LFLAGS = +cpm -subtype=cpc -create-app
amstrad_cpm: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

amstrad_pcw40: CFLAGS = +cpm
amstrad_pcw40: LFLAGS = +cpm -subtype=pcw40 -create-app
amstrad_pcw40: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

amstrad_pcw80: CFLAGS = +cpm
amstrad_pcw80: LFLAGS = +cpm -subtype=pcw80 -create-app
amstrad_pcw80: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

attache: CFLAGS = +cpm
attache: LFLAGS = +cpm -subtype=attache -create-app
attache: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

bic: CFLAGS = +cpm
bic: LFLAGS = +cpm -subtype=bic -create-app
bic: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

bondwell: CFLAGS = +cpm
bondwell: LFLAGS = +cpm -subtype=bondwell -create-app
bondwell: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

bondwell2: CFLAGS = +cpm
bondwell2: LFLAGS = +cpm -subtype=bw2 -create-app
bondwell2: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

c128: CFLAGS = +c128
c128: LFLAGS = +c128 -lc128cpm -subtype=disk -create-app
c128: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

einstein: CFLAGS = +cpm
einstein: LFLAGS = +cpm -subtype=einstein -create-app
einstein: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

excali64: CFLAGS = +cpm
excali64: LFLAGS = +cpm -subtype=excali64 -create-app
excali64: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

kaypro83: CFLAGS = +cpm
kaypro83: LFLAGS = +cpm -subtype=kaypro83 -create-app
kaypro83: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

kaypro84: CFLAGS = +cpm
kaypro84: LFLAGS = +cpm -subtype=kaypro84 -create-app
kaypro84: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

lynx128: CFLAGS = +cpm
lynx128: LFLAGS = +cpm -subtype=lynx -create-app
lynx128: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

microbee: CFLAGS = +cpm
microbee: LFLAGS = +cpm -subtype=microbee -create-app
microbee: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

msxdos: CFLAGS = +msx
msxdos: LFLAGS = +msx -subtype=msxdos -create-app
msxdos: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

msxdos2: CFLAGS = +msx -DUSE_FOLDERS
msxdos2: LFLAGS = +msx -subtype=msxdos2 -DUSE_FOLDERS -create-app
msxdos2: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

mz2500: CFLAGS = +cpm
mz2500: LFLAGS = +cpm -subtype=mz2500 -create-app
mz2500: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

nascom: CFLAGS = +cpm
nascom: LFLAGS = +cpm -subtype=nascom -create-app
nascom: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

newbrain: CFLAGS = +cpm
newbrain: LFLAGS = +cpm -lnewbrain_cpm -create-app
newbrain: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

osborne1: CFLAGS = +cpm
osborne1: LFLAGS = +cpm -subtype=osborne1 -create-app
osborne1: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

pc8801: CFLAGS = +pc88
pc8801: LFLAGS = +pc88 -subtype=disk -create-app
pc8801: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

px4: CFLAGS = +cpm
px4: LFLAGS = +cpm -subtype=px4 -create-app
px4: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

qc10: CFLAGS = +cpm
qc10: LFLAGS = +cpm -subtype=qc10 -create-app
qc10: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

rc700: CFLAGS = +cpm
rc700: LFLAGS = +cpm -subtype=rc700 -create-app
rc700: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

sharpx1: CFLAGS = +cpm
sharpx1: LFLAGS = +cpm -subtype=x1 -create-app
sharpx1: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

smc777: CFLAGS = +cpm
smc777: LFLAGS = +cpm -subtype=smc777 -create-app
smc777: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

svi: CFLAGS = +cpm
svi: LFLAGS = +cpm -subtype=svi -create-app
svi: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

tiki100: CFLAGS = +cpm
tiki100: LFLAGS = +cpm -subtype=tiki100 -create-app
tiki100: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

zxplus3: CFLAGS = +zx
zxplus3: LFLAGS = +zx -subtype=plus3 -lp3 -create-app
zxplus3: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

zxplus3_cpm: CFLAGS = +cpm
zxplus3_cpm: LFLAGS = +cpm -subtype=zxplus3 -create-app
zxplus3_cpm: $(OBJS)
	mkdir -p $@
	$(CC) $(LFLAGS) -o $@/$(OUT) $^

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c -o $@ $<

# clean house
clean:
	rm -f $(OBJS)
