/*#####################################################################
## PROJECT LINKER SCRIPT
## SINCE 0.1.0.0
## UPDATED 0.1.0.1
## This file contains the GCC linker script required to map the 
## project binary into a structure both the hardware and our software 
## can understand.
##
## Copyright (c) 2025 Israfil Argos
## This file is under the AGPLv3. For information on what that 
## entails, see the attached LICENSE.md file or 
## https://www.gnu.org/licenses/agpl-3.0.en.html.
#####################################################################*/

OUTPUT_FORMAT("elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)
ENTRY(efi_main)

/* 
    This is complete magic to me. Taken from
    https://wiki.osdev.org/User:Xenos/UEFI_Bare_Bones.
*/
SECTIONS
{
	. = 4096;
	ImageBase = .;
	.hash : { *(.hash) }
	.gnu.hash : { *(.gnu.hash) }
	. = ALIGN(4096);
	.text :
	{
		_text = .;
		*(.text)
		*(.text*)
		*(.gnu.linkonce.t.*)
		. = ALIGN(16);
	}
	_etext = .;
	_text_size = . - _text;
	. = ALIGN(4096);
	.rdata :
	{
		_data = .;
		*(.got.plt)
		*(.got)
		*(.rodata*)
		*(.srodata)
		*(.gnu.linkonce.r.*)
	}
	. = ALIGN(4096);
	.data :
	{
		*(.data*)
		*(.sdata*)
		*(.gnu.linkonce.d.*)
	}
	. = ALIGN(4096);
	.bss :
	{
		*(.sbss)
		*(.scommon)
		*(.dynbss)
		*(.bss)
		*(.gnu.linkonce.b.*)
		*(COMMON)
	}
	. = ALIGN(4096);
	.dynamic  : { *(.dynamic) }
	. = ALIGN(4096);
	.rel :
	{
		*(.rel.data)
		*(.rel.data.*)
		*(.rel.got)
		*(.rel.stab)
	}
	_edata = .;
	_data_size = . - _etext;
	. = ALIGN(4096);
	.reloc :
	{
		LONG(_data);
		LONG(10);
		SHORT(0);
		*(.reloc)
	}
	. = ALIGN(4096);
	.dynsym   : { *(.dynsym) }
	. = ALIGN(4096);
	.dynstr   : { *(.dynstr) }
	. = ALIGN(4096);
	/DISCARD/ :
	{
		*(.rel.reloc)
		*(.eh_frame)
		*(.note*)
		*(.comment*)
	}
}
