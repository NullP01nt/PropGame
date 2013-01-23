######################
# segloader Makefile #
######################

NAME=segloader
BOARD=GAMEBLADE
MODEL=xmmc

SPINDIR=./spin

HDRS= fileio.h\
	  gamepad.h\
	  pins.h\
	  vga_text.h

OBJS=\
segloader.o\
printf.o\
fileio.o\
gamepad.o\
pins.o\
VGA_firmware.o\
vga_text.o

CFLAGS = -Os -DPROPELLER_GCC

include ../common/common.mk
