######################
# sd_loader Makefile #
######################

ifndef BUILDROOT
BUILDROOT=.
endif

SRCDIR=.
OBJDIR=$(BUILDROOT)/obj
DRVDIR=$(BUILDROOT)/include

DIRS = $(OBJDIR) $(DRVDIR)

CC=propeller-elf-gcc
ECHO=echo
MKDIR=mkdir -p
RM=rm
BSTC=bstc.linux

CFLAGS=-Os -Wall -mlmm

HDRS=\
	 cacheops.h\
	 debug.h\
	 fatread.h\
	 gamepad.h\
	 menudraw.h\
	 pex.h\
	 pins.h\
	 sdio.h\
	 sd_loader.h\
	 vga_text.h\
	 vm_start.h

all:	$(DRVDIR)/sd_cache_menu.elf

SDCACHELOADER_OBJS=\
				   $(OBJDIR)/fatread.o\
				   $(OBJDIR)/gamepad.o\
				   $(OBJDIR)/menudraw.o\
				   $(OBJDIR)/pins.o\
				   $(OBJDIR)/sd_cache_loader.o\
				   $(OBJDIR)/sdio.o\
				   $(OBJDIR)/VGA_firmware.o\
				   $(OBJDIR)/vga_text.o\
				   $(OBJDIR)/vm_start.o

$(DRVDIR)/sd_cache_menu.elf:	$(DRVDIR) $(SDCACHELOADER_OBJS)
	propeller-elf-gcc $(CFLAGS) -o $@ $(SDCACHELOADER_OBJS)

#########
# RULES #
#########

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(OBJDIR) $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@
	@$(ECHO) $@

$(OBJDIR)/%.o:	$(SRCDIR)/%.S $(OBJDIR) $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@
	@$(ECHO) $@

$(SRCDIR)/%.dat: $(SRCDIR)/%.spin
	$(BSTC) -Ogxr -c -o $(basename $@) $<

$(OBJDIR)/%_firmware.o: $(SRCDIR)/%.dat
	propeller-elf-objcopy -I binary -B propeller -O $(CC) $< $@

###############
# DIRECTORIES #
###############

$(DIRS):
	$(MKDIR) $@

################
# CLEAN TARGET #
################

.PHONY:	clean
clean:
	@$(RM) -f -r $(OBJDIR)
	@$(RM) -rf $(DRVDIR)
