#!/bin/bash

dd if=/dev/zero of=fssetter.img bs=512 count=1440
MTOOLSRC=mtoolsrc mformat -f 720 -v FSSETTER a:
MTOOLSRC=mtoolsrc mcopy -sv binaries/* a:
