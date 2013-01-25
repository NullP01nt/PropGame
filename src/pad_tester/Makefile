#######################
# pad_tester Makefile #
#######################

NAME=pad_tester
BOARD=GAMEBLADE
MODEL=xmmc

SPINDIR=./spin

HDRS=\
	 gamepad.h\
	 menudraw.h\
	 pins.h\
	 vga_text.h

OBJS=\
	 gamepad.o\
	 menudraw.o\
	 pad_tester.o\
	 pins.o\
	 VGA_firmware.o\
	 vga_text.o

CFLAGS = -Os -DPROPELLER_GCC -m32bit-doubles -mfcache

include ../common/common.mk
