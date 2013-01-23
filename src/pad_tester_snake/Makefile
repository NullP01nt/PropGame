######################
# sd_loader Makefile #
######################

ifndef BUILDROOT
BUILDROOT=.
endif

SRCDIR=.
OBJDIR=$(BUILDROOT)/obj
DRVDIR=$(BUILDROOT)/build

DIRS = $(OBJDIR) $(DRVDIR)

CC=propeller-elf-gcc
ECHO=echo
MKDIR=mkdir -p
RM=rm

CFLAGS=-Os -Wall -mlmm

HDRS=pins.h vga.h gamepad.h

all:	$(DRVDIR)/pad_tester.elf

OBJS=\
$(OBJDIR)/pins.o \
$(OBJDIR)/vga.o \
$(OBJDIR)/gamepad.o \
$(OBJDIR)/pad_tester.o

$(DRVDIR)/pad_tester.elf:	$(DRVDIR) $(OBJS)
	propeller-elf-gcc $(CFLAGS) -o $@ $(OBJS)

#########
# RULES #
#########

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(OBJDIR) $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@
	@$(ECHO) $@

$(OBJDIR)/%.o:	$(SRCDIR)/%.S $(OBJDIR) $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@
	@$(ECHO) $@

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
	@$(RM) -rf $(OBJDIR)
	@$(RM) -rf $(DRVDIR)

.PHONY: run
run: $(DRVDIR)/pad_tester.elf
	propeller-load -I $(BUILDROOT) -bGAMEBLADE -r -S -t $(DRVDIR)/pad_tester.elf
