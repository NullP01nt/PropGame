# #########################################################
# This makefile fragment builds LMM/XMM/XMMC demo programs
#   
# To use it, define:
#  PROPLIB to be the path to this directory
#  NAME to be the name of project
#       - this is used to create the final program $(NAME).elf
#  OBJS to be the object files needed for the project
#  MODEL to lmm, xmm, or xmmc
#  CFLAGS to be desired CFLAGS
#
#  Then set up a default "all" target (normally this will be
#    all: $(NAME).elf
#  and finally
#    include $(PROPLIB)/demo.mk
#
# Copyright (c) 2011 Parallax Inc.
# All rights MIT licensed
# #########################################################

# where we installed the propeller binaries and libraries
PREFIX = /opt/parallax

ifndef MODEL
MODEL=lmm
endif

ifndef BOARD
BOARD=GAMEBLADE
endif

ifneq ($(BOARD),)
BOARDFLAG=-b$(BOARD)
endif

ifndef NAME
NAME=output
endif

CFLAGS_NO_MODEL := $(CFLAGS)
CFLAGS += -m$(MODEL)
CXXFLAGS += $(CFLAGS)
LDFLAGS += -m$(MODEL) -fno-exceptions -fno-rtti

ifneq ($(LDSCRIPT),)
LDFLAGS += -T $(LDSCRIPT)
endif

# basic gnu tools
CC = propeller-elf-gcc
CXX = propeller-elf-g++
LD = propeller-elf-ld
AS = propeller-elf-as
AR = propeller-elf-ar
OBJCOPY = propeller-elf-objcopy
LOADER = propeller-load

ECHO=echo
MKDIR=mkdir -p
RM=rm

# BSTC program
BSTC=bstc.linux
SPINDIR=.

ifneq ($(NAME),)
$(NAME).elf: $(BINDIR) $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)
endif

ifneq ($(LIBNAME),)
lib$(LIBNAME).a: $(OBJS)
	$(AR) rs $@ $(OBJS)
endif


### OBJECTS ###
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -o $@ -c $<
	@$(ECHO) $@

%.o: %.cpp $(HDRS)
	$(CC) $(CXXFLAGS) -o $@ -c $<
	@$(ECHO) $@

%.o: %.S $(HDRS)
	$(CC) -o $@ -c $<
	@$(ECHO) $@

#
# a .cog program is an object file that contains code intended to
# run in a COG separate from the main program; i.e., it's a COG
# driver that the linker will place in the .text section.
#
%.cog: %.c
	$(CC) $(CFLAGS_NO_MODEL) -mcog -r -o $@ $<
	$(OBJCOPY) --localize-text --rename-section .text=$@ $@

%.cog: %.cogc
	$(CC) $(CFLAGS_NO_MODEL) -mcog -xc -r -o $@ $<
	$(OBJCOPY) --localize-text --rename-section .text=$@ $@

#
# a .ecog program is an object file that contains code intended to
# run in a COG separate from the main program; i.e., it's a COG
# driver that the linker will place in the .drivers section which
# gets loaded to high EEPROM space above 0x8000.
#
%.ecog: %.c
	$(CC) $(CFLAGS_NO_MODEL) -mcog -r -o $@ $<
	$(OBJCOPY) --localize-text --rename-section .text=$@ $@

%.ecog: %.ecogc
	$(CC) $(CFLAGS_NO_MODEL) -mcog -xc -r -o $@ $<
	$(OBJCOPY) --localize-text --rename-section .text=$@ $@

%.binary: %.elf
	$(LOADER) -s $<

%.dat: %.spin
	$(BSTC) -Ox -c -o $(basename $@) $<

%_firmware.o: %.dat
	$(OBJCOPY) -I binary -B propeller -O $(CC) $< $@

.PHONY: clean
clean:
	$(RM) -f *.o *.elf *.a *.cog *.ecog *.binary *.dat

.PHONY: run
run: $(NAME).elf
	$(LOADER) $(BOARDFLAG) $(NAME).elf -r -S -t
