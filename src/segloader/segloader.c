#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cog.h>
#include <ctype.h>
#include <propeller.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/sd.h>

#undef CALL_MOUNT
#undef SPINNERET_CARD
#undef PROP_BOE
#undef C3_CARD
#undef PARALLEL_SPI

#include "fileio.h"
#include "vga_text.h"
#include "gamepad.h"

uint8_t PAD_ONE;

extern _Driver _SimpleSerialDriver;
extern _Driver _FileDriver;

_Driver *_driverlist[] = {
	&_SimpleSerialDriver,
	&_FileDriver,
	NULL
};

int main(int argc, char** argv) {
	InitGPadIO();
	vgaText_start(16); // Start VGA on base 16

	vgaText_print("Hello, Imara\n");
	vgaText_print("Hello, Xander\n");
	vgaText_print("--- PEX Files ---\n");
	listFilesByExt(NULL,"pex");
	vgaText_print("\n--- All Files ---\n");
	listFiles(NULL);
	while(1);
	return 0;
}
