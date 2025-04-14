#!/bin/bash

cd Cobalt
dd if=/dev/zero of=$1.img bs=1k count=1440
mformat -i $1.img -f 1440 ::
mmd -i $1.img ::/EFI
mmd -i $1.img ::/EFI/BOOT
mcopy -i $1.img BOOTX64.efi ::/EFI/BOOT
echo Created FAT image.
