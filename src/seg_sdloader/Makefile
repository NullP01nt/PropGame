######################
# segloader Makefile #
######################

NAME=seg_sdloader
BOARD=GAMEBLADE
MODEL=lmm

HDRS=\
	 cacheops.h\
	 debug.h\
	 fatread.h\
	 gamepad.h\
	 pex.h\
	 pins.h\
	 sdio.h\
	 seg_sdloader.h\
	 vga_text.h\
	 vm_start.h

OBJS=\
	 cache_interface_firmware.o\
	 fatread.o\
	 gamepad.o\
	 pins.o\
	 sd_driver_firmware.o\
	 sdio.o\
	 seg_sdloader.o\
	 VGA_firmware.o\
	 vga_text.o\
	 vm_start.o

CFLAGS = -Os -DPROPELLER_GCC

include ../common/common.mk
