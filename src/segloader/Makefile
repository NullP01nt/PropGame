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

HDRS= fileio.h

all:	$(DRVDIR)/segloader.elf

OBJS=\
$(OBJDIR)/segloader.o\
$(OBJDIR)/printf.o\
$(OBJDIR)/fileio.o

$(DRVDIR)/segloader.elf:	$(DRVDIR) $(OBJS)
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
run: $(DRVDIR)/segloader.elf
	propeller-load -I $(BUILDROOT) -bGAMEBLADE -r -S -t $(DRVDIR)/pad_tester.elf
