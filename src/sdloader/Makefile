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

HDRS=sd_loader.h fatread.h sdio.h pex.h

all:	$(DRVDIR)/sd_loader.elf

SDLOADER_OBJS=\
$(OBJDIR)/sd_loader.o \
$(OBJDIR)/fatread.o \
$(OBJDIR)/sdio.o \
$(OBJDIR)/vm_start.o

$(DRVDIR)/sd_loader.elf:	$(DRVDIR) $(SDLOADER_OBJS)
	propeller-elf-gcc $(CFLAGS) -o $@ $(SDLOADER_OBJS)

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
