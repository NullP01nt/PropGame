CC=propeller-elf-gcc
MODEL=xmmc
CFLAGS=-Os -m$(MODEL)
LDFLAGS=-m$(MODEL)
OBJDIR=./
SRCDIR=./
OBJS = vgademo.o vga.o draw.o text.o text2.o
HDRS =

vgademo.elf:	$(OBJS)
	@$(CC) $(LDFLAGS) $(OBJS) -o $@ -s

clean:
	rm -f *.o *.elf

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(HDRS)
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: run
run	: vgademo.elf
	propeller-load -I./ -bGAMEBLADE -r -S -t vgademo.elf
